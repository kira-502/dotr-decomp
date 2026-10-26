"""tools/mod_spread.py F|--all [--jobs 8] [--no-accept] [--consts] : spread a finished code-module function to its family
(15 Oct). WSL, game folder.

The 762 modules repeat much of their code (tools/modpiles.py: 4,146 functions in 128 families of 10+). A copy in
another module has the same instructions, but its calls to sibling functions and its module data sit at other
addresses, so `dk twins` (which renames only the function) can't move it. This takes F's C from src/mod/, finds
every unfinished function with F's opcode shape, lines the two asm listings up instruction by instruction and
renames each symbol F uses to the one the copy uses there (func_01E001A0_b000 -> func_01E00220_b081,
D_01E06480_b000 -> ...); --consts also swaps immediates that differ (a literal that appears once in F's C).
F's own `#pragma` lines (an -O1/-O2/-O3 function) go with it, with their `#pragma ... reset` lines after it.
Each candidate goes through `dk try`; the ones that MATCH and fit are accepted together (`dk accept-many`,
one build). Candidates: work/modfam/<copy>.c."""
from __future__ import annotations

import argparse
import os
import re
import shlex
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

root = Path.cwd()
DK = shlex.split(os.environ.get("DK", "dk"))  # DK='python3 /path/dk.py' for a kit worktree
WORD = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)$")
SYM = re.compile(r"\b(?:func|D|jtbl)_[0-9A-F]{6,8}(?:_\w+)?\b")
IMM = re.compile(r"(?<![\w.])-?0x[0-9A-Fa-f]+\b|(?<![\w.$%])-?\d+\b")


def listing(path: Path) -> list[tuple[int, str, str]]:
    """(word, mnemonic, operands) per instruction of one function's asm"""
    out = []
    for ln in path.read_text().split("endlabel")[0].splitlines():
        m = WORD.search(ln)
        if m:
            out.append((int.from_bytes(bytes.fromhex(m.group(2)), "little"), m.group(3), m.group(4).strip()))
    return out


def shape(lst) -> tuple:
    return tuple(w >> 26 if w >> 26 else 0x40 | (w & 0x3F) for w, _, _ in lst)


TYPEDEF = re.compile(r"^typedef\s+(?:struct|union)\s*\w*\s*\{[^{}]*\}\s*(\w+);\n", re.M)


def function_c(name: str) -> str | None:
    """F's definition, with the file's typedefs it uses in front (a copy goes to another module's file)"""
    for cfile in sorted(root.glob("src/mod/*.c")):
        text = cfile.read_text()
        m = re.search(rf"^[A-Za-z_][\w \t\*]*?\b{name}\s*\([^;{{]*\)\s*\{{", text, re.M)
        if not m:
            continue
        depth = 0
        for i in range(m.end() - 1, len(text)):
            depth += {"{": 1, "}": -1}.get(text[i], 0)
            if depth == 0:
                body = text[m.start():i + 1]
                # typedefs the body uses, and the ones those use (Mod-D, 25 Oct: nested struct types)
                defs = list(TYPEDEF.finditer(text[:m.start()]))
                need, grew = body, True
                used: set[int] = set()
                while grew:
                    grew = False
                    for k, t in enumerate(defs):
                        if k not in used and re.search(rf"\b{t.group(1)}\b", need):
                            used.add(k)
                            need += t.group(0)
                            grew = True
                # the function's own #pragma lines (an -O1/-O2/-O3 twin) and comments right above it, and the
                # pragmas' resets after it
                before = text[:m.start()].split("\n")[:-1]
                lead: list[str] = []
                while before and (not before[-1].strip() or before[-1].lstrip().startswith(("#pragma", "/*", "*"))):
                    ln = before.pop()
                    if not ln.rstrip().endswith(" reset"):
                        lead.insert(0, ln)
                while lead and not lead[0].strip():
                    lead.pop(0)
                prags = any(ln.startswith("#pragma") for ln in lead)
                after = re.match(r"(?:[ \t]*\n)*((?:#pragma \w+ reset[ \t]*\n)+)", text[i + 1:].lstrip("\n") + "\n")
                resets = after.group(1) if after and prags else ""
                head = "".join(ln + "\n" for ln in lead)
                # the shape's description comment, right above its first typedef
                first = min((defs[k].start() for k in used), default=m.start())
                note = re.search(r"(/\* shape [^\n]*(?:\n(?!\s*\*/)[^\n]*)*?\*/\n)\s*\Z", text[:first])
                return ((note.group(1) + "\n" if note else "") + "".join(defs[k].group(0) + "\n" for k in sorted(used))
                        + head + body + "\n" + resets)
    return None


def mapping(src, dst, consts: bool) -> tuple[dict[str, str], dict[int, int]] | None:
    syms: dict[str, str] = {}
    nums: dict[int, int] = {}
    for (_, _, a), (_, _, b) in zip(src, dst):
        sa, sb = SYM.findall(a), SYM.findall(b)
        if len(sa) != len(sb):
            return None
        for x, y in zip(sa, sb):
            if syms.setdefault(x, y) != y:
                return None  # one symbol of F is two different ones in the copy
        if consts:
            ia, ib = IMM.findall(SYM.sub("", a)), IMM.findall(SYM.sub("", b))
            if len(ia) == len(ib):
                for x, y in zip(ia, ib):
                    if x != y:
                        nums[int(x, 0)] = int(y, 0)
    return syms, nums


def rewrite(c: str, f: str, g: str, syms: dict[str, str], nums: dict[int, int]) -> str | None:
    c = re.sub(rf"\b{f}\b", g, c)
    if syms:
        c = re.sub(r"\b(?:func|D|jtbl)_[0-9A-F]{6,8}(?:_\w+)?\b", lambda m: syms.get(m.group(0), m.group(0)), c)
    for x, y in nums.items():
        hits = [m for m in re.finditer(r"(?<![\w.])(0x[0-9A-Fa-f]+|\d+)\b", c) if int(m.group(1), 0) == abs(x)]
        if len(hits) != 1:
            return None  # the literal is not there once: leave that copy to a person
        m = hits[0]
        c = c[:m.start()] + (hex(abs(y)) if m.group(1).startswith("0x") else str(abs(y))) + c[m.end():]
    return '#include "common.h"\n#include "game.h"\n\n' + c + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("func", nargs="?")
    ap.add_argument("--all", action="store_true", help="every finished module function is a source")
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--no-accept", action="store_true")
    ap.add_argument("--consts", action="store_true")
    a = ap.parse_args()
    if not a.all and not a.func:
        ap.error("name a finished function or pass --all")
    pending = {m.group(1) for cf in root.glob("src/mod/*.c")
               for m in re.finditer(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\);', cf.read_text())}
    by_shape: dict[tuple, list] = {}
    for path in root.glob("asm/nonmatchings/mod/*/*.s"):
        if path.stem in pending:
            lst = listing(path)
            by_shape.setdefault(shape(lst), []).append((path.stem, lst))
    # --all: every finished module function is a source (after a day of accepts, one pass spreads them all)
    sources = sorted(p.stem for p in root.glob("asm/matchings/mod/*/*.s")) if a.all else [a.func]
    good: list[str] = []
    for f in sources:
        good += spread(f, by_shape, pending - set(good), a, quiet=len(sources) > 1)
    print(f"{len(good)} copies match in all")
    if good and not a.no_accept:
        r = subprocess.run([*DK, "accept-many", "--dir", str(root / "work/modfam"), *good], cwd=root,
                           capture_output=True, text=True)
        print("\n".join((r.stdout + r.stderr).strip().splitlines()[-6:]))


def spread(f: str, by_shape: dict, pending: set, a, quiet: bool) -> list[str]:
    src_asm = next(root.glob(f"asm/matchings/mod/*/{f}.s"), None) or next(root.glob(f"asm/nonmatchings/mod/*/{f}.s"),
                                                                           None)
    c = function_c(f)
    if not src_asm or c is None:
        if quiet:
            return []
        raise SystemExit(f"{f}: needs its asm and its C in src/mod/ (accept it first)")
    src = listing(src_asm)
    copies = [(g, lst) for g, lst in by_shape.get(shape(src), []) if g in pending and g != f]
    if not copies:
        return []
    out = root / "work/modfam"
    out.mkdir(parents=True, exist_ok=True)

    def attempt(item):
        g, lst = item
        mp = mapping(src, lst, a.consts)
        if mp is None:
            return g, "symbols do not line up"
        text = rewrite(c, f, g, *mp)
        if text is None:
            return g, "a differing constant is not in the C once"
        (out / f"{g}.c").write_text(text)
        r = subprocess.run([*DK, "try", g, str(out / f"{g}.c"), "--lines", "0"], cwd=root, capture_output=True,
                           text=True)
        first = (r.stdout.strip().splitlines() or [""])[0]
        return g, ("MATCH" if first.startswith(f"MATCH {g}") else first[:100])

    with ThreadPoolExecutor(a.jobs) as ex:
        results = list(ex.map(attempt, copies))
    good = sorted(g for g, why in results if why == "MATCH")
    if not quiet:
        for g, why in sorted(results):
            if why != "MATCH":
                print(f"  {g}: {why}")
    print(f"{f}: {len(good)} of {len(copies)} unfinished functions with its shape match")
    return good


if __name__ == "__main__":
    main()
