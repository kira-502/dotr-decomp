#!/usr/bin/env python3
"""The game's code modules: 762 Metrowerks overlays ("MWo3") in DATA/BMODULE.MRG, CMODULE.MRG and MMODULE.MRG.
Every module file loads whole at 0x1E00000, header included, so its code starts at 0x1E00080 (the calls inside a
module land on function starts only with that base: 11,959 of 11,991). A module file is a 128-byte header, then
.text, then .data:

  magic "MWo3" | slot (the module's number among the ELF's 834 placeholder segments) | entry | text size |
  data size | bss size | load callback (start, end: both text+data end + 0x40) | name[32] ("b000.bin") | 64 x 0

Commands (run in the game folder, the toolchain loaded):
  extract          read the disc (dk.local.json) -> assets/modules/<name>.mwo (untracked, like the exe) and
                   config/modules.tsv (tracked: one row per module with its sha1); checks the sha1s if the table
                   exists
  split [N ...]    split the modules (make split-modules runs it)
  ld [N ...]       write linker/mod/<name>.ld again (split does; after a change to the linker script's form)
  pack N ELF OUT   linked module ELF -> MWo3 file (header fields from config/modules.tsv, sizes from the ELF)
  check [N ...]    compare build/modules/<name>.mwo with config/modules.tsv's sha1 (all modules by default)
"""
from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parent.parent
TABLE = ROOT / "config/modules.tsv"
OUT_DIR = ROOT / "assets/modules"
MRGS = ("DATA/BMODULE.MRG", "DATA/CMODULE.MRG", "DATA/MMODULE.MRG")
COLS = ["name", "mrg", "offset", "slot", "entry", "text", "data", "bss", "cb_start", "cb_end", "sha1"]
HEADER = struct.Struct("<4s7I32s64s")


def read_table() -> dict[str, dict[str, Any]]:
    rows = {}
    for ln in TABLE.read_text().splitlines():
        if not ln or ln.startswith("#") or ln.startswith("name\t"):
            continue
        r: dict[str, Any] = dict(zip(COLS, ln.split("\t")))
        for k in ("offset", "slot", "entry", "text", "data", "bss", "cb_start", "cb_end"):
            r[k] = int(r[k], 0)
        rows[r["name"]] = r
    return rows


def disc_path() -> str:
    """Your own disc image: $DK_DISC, else "disc" in dk.local.json (not in git), else dk.json."""
    if os.environ.get("DK_DISC"):
        return os.environ["DK_DISC"]
    for name in ("dk.local.json", "dk.json"):
        f = ROOT / name
        if f.exists() and Path(disc := json.loads(f.read_text()).get("disc", "")).is_file():
            return disc
    sys.exit("modules: no disc image: put its path in dk.local.json ({\"disc\": \"/path/to/your.iso\"}) or DK_DISC")


def disc_reader():
    dk = shutil.which("dk")  # the kit's disc reader, next to dk
    if not dk:
        sys.exit("dk is not on PATH: load the toolchain first (. ~/decomp/toolchain/env.sh)")
    sys.path.insert(0, str(Path(dk).resolve().parent))
    from dklib.disc import Disc  # noqa: E402
    return Disc(disc_path())


def extract() -> None:
    disc = disc_reader()
    known = read_table() if TABLE.exists() else None
    rows, bad = [], []
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    for mrg in MRGS:
        e = disc.find(mrg)
        blob = disc.read(e.lba, (e.size + 2047) // 2048)[:e.size]
        # modules sit at 32 KB steps; a slot holds one module (BMODULE: exactly one slot each, CMODULE: 1-6 slots,
        # MMODULE: one module, the rest filler)
        for off in range(0, len(blob), 0x8000):
            if blob[off:off + 4] != b"MWo3":
                continue
            magic, slot, entry, ts, ds, bs, cb0, cb1, fname, pad = HEADER.unpack_from(blob, off)
            name = fname.split(b"\0")[0].decode("ascii").rsplit(".", 1)[0]
            image = blob[off:off + HEADER.size + ts + ds]
            sha = hashlib.sha1(image).hexdigest()
            (OUT_DIR / f"{name}.mwo").write_bytes(image)
            rows.append([name, mrg.split("/")[1], hex(off), str(slot), hex(entry), hex(ts), hex(ds), hex(bs),
                         hex(cb0), hex(cb1), sha])
            if known is not None and (name not in known or known[name]["sha1"] != sha):
                bad.append(name)
    if known is None:
        rows.sort(key=lambda r: r[0])
        TABLE.write_text("\t".join(COLS) + "\n" + "".join("\t".join(r) + "\n" for r in rows))
        print(f"{len(rows)} modules -> {OUT_DIR.relative_to(ROOT)}/, table written to {TABLE.relative_to(ROOT)}")
    elif bad:
        sys.exit(f"{len(bad)} modules differ from {TABLE.name}: {bad[:8]}")
    else:
        print(f"{len(rows)} modules -> {OUT_DIR.relative_to(ROOT)}/, all match {TABLE.name}")


SKIP_SYM = re.compile(r"^(\.|L\d|gcc2_compiled|__gnu_compiled|_MACRO_INC_GUARD|\w+_(VRAM|VRAM_END|TEXT_START|bss_VRAM)$)")


def main_syms() -> Path:
    """build/main.elf's names (with sizes) as a splat symbol list, so module code that calls or reads the main
    program uses the main program's names (func_001A23B0, D_00317490 + 0x6D8 for an address inside an object)"""
    elf = ROOT / "build/main.elf"
    if not elf.exists():
        sys.exit("build/main.elf is missing: build the main program first (make build)")
    nm = subprocess.run(["mipsel-none-elf-nm", "-S", "--defined-only", str(elf)], capture_output=True, text=True,
                        check=True).stdout
    out = ROOT / "linker/mod/main_syms.txt"
    out.parent.mkdir(parents=True, exist_ok=True)
    lines = []
    seen: dict[int, str] = {}
    rows = []
    for ln in nm.splitlines():
        p = ln.split()
        addr, kind, name = int(p[0], 16), p[-2], p[-1]
        size = int(p[1], 16) if len(p) == 4 else 0
        if SKIP_SYM.match(name) or "." in name or addr >= 0x1E00000:
            continue
        rows.append((addr, kind, name, size))
    # one name per address (splat refuses two): the generated func_/D_/jtbl_ name the headers use wins over an alias
    rows.sort(key=lambda r: (r[0], not re.match(r"^(func|D|jtbl)_[0-9A-F]{8}$", r[2])))
    # a function's old name (config/old_names.txt, a linker-script alias) has no type or size: it takes its own
    old_path = ROOT / "config/old_names.txt"
    old = set(re.findall(r"^(func_[0-9A-F]{8}) = ", old_path.read_text(), re.M)) if old_path.exists() else set()
    sizes = {r[0]: r[3] for r in rows if r[3]}
    for addr, kind, name, size in rows:
        if name in old:
            kind, size = "T", size or sizes.get(addr, 0)
        if addr in seen:
            continue
        seen[addr] = name
        attrs = (["type:func"] if kind in "Tt" else ["type:jtbl"] if name.startswith("jtbl_") else []) + \
            ([f"size:0x{size:X}"] if size else [])
        lines.append(f"{name} = 0x{addr:08X};" + (f" // {' '.join(attrs)}" if attrs else ""))
    out.write_text("\n".join(lines) + "\n")
    return out


YAML = """name: {name}
sha1: {sha1}
options:
  basename: {name}
  target_path: assets/modules/{name}.mwo
  base_path: ../..
  platform: ps2
  compiler: EEGCC
  asm_path: asm
  src_path: src
  build_path: build
  ld_script_path: build/modsplit/{name}.splat.ld
  symbol_addrs_path:
    - linker/mod/main_syms.txt
  undefined_funcs_auto_path: linker/mod/{name}.funcs.txt
  undefined_syms_auto_path: linker/mod/{name}.syms.txt
  find_file_boundaries: False
  disassemble_all: True
  o_as_suffix: False
  use_legacy_include_asm: False
  asm_function_macro: glabel
  asm_jtbl_label_macro: jlabel
  asm_data_macro: dlabel
  generate_asm_macros_files: False
  section_order: [".text", ".data", ".rodata", ".sdata", ".sbss", ".bss"]
  subalign: 4
  string_encoding: ASCII
  data_string_encoding: ASCII
  rodata_string_guesser_level: 2
  data_string_guesser_level: 2
  ld_bss_is_noload: True
segments:
  - [0x0, bin, mod_header_{name}]
  - name: {name}
    type: code
    start: 0x80
    vram: 0x1E00080
    symbol_name_format: $VRAM_$SEG
    bss_size: {bss:#x}
    subsegments:
      - [0x80, c, mod/{name}]
{data}  - [{end:#x}]
"""


def split(jobs: int = 8, only: list[str] | None = None) -> None:
    """every module -> asm/nonmatchings/mod/<name>/<func>.s, asm/data/mod/<name>.data.s, src/mod/<name>.c (an
    existing C file is kept: splat never overwrites one), linker/mod/<name>.{funcs,syms}.txt"""
    main_syms()
    table = read_table()
    names = only or sorted(table)
    cfg = ROOT / "build/modsplit"
    cfg.mkdir(parents=True, exist_ok=True)
    for n in names:
        r = table[n]
        pool = pool_start(n, r)
        data = (f"      - [{0x80 + pool:#x}, rodata, mod/{n}_pool]\n" if pool < r["text"] else "") + \
            (f"      - [{0x80 + r['text']:#x}, data, mod/{n}]\n" if r["data"] else "")
        (cfg / f"{n}.yaml").write_text(YAML.format(name=n, sha1=r["sha1"], bss=r["bss"], data=data,
                                                   end=0x80 + r["text"] + r["data"]))

    def run(n: str) -> tuple[str, int, str]:
        # a relative config path: splat writes INCLUDE_ASM paths relative to it (asm/nonmatchings/mod/<name>)
        p = subprocess.run([sys.executable, "-m", "splat", "split", f"build/modsplit/{n}.yaml"], cwd=ROOT,
                           capture_output=True, text=True)
        return n, p.returncode, (p.stdout + p.stderr)[-600:]

    bad = []
    with ThreadPoolExecutor(jobs) as ex:
        for n, rc, log in ex.map(run, names):
            if rc:
                bad.append(n)
                print(f"split {n} failed:\n{log}", file=sys.stderr)
    if bad:
        sys.exit(f"{len(bad)} modules failed to split: {bad[:10]}")
    for n in names:
        write_ld(n, table[n])
    write_mk(table)
    print(f"split {len(names)} modules")


def pool_start(n: str, r: dict[str, Any]) -> int:
    """where .text's code ends and Metrowerks' literal pool (float constants) begins: after the last `jr $ra` and
    its delay slot, rounded up to 8 (text offset; == text size when there is no pool)"""
    img = (OUT_DIR / f"{n}.mwo").read_bytes()
    words = struct.unpack_from(f"<{r['text'] // 4}I", img, HEADER.size)
    last = max((k for k, w in enumerate(words) if w == 0x03E00008), default=None)
    if last is None:
        return r["text"]
    end = (last + 2) * 4
    end = (end + 7) & ~7
    return min(end, r["text"]) if any(words[end // 4:]) else r["text"]


LD = """{aliases}SECTIONS
{{
    .text 0x1E00080 : SUBALIGN(4)
    {{
        FILL(0x00000000);
        build/src/mod/{n}.c.o(.text);
{pool}    }}
    .data : SUBALIGN(4)
    {{
        FILL(0x00000000);
{data}    }}
    .bss (NOLOAD) : SUBALIGN(4)
    {{
        build/src/mod/{n}.c.o(.bss);
    }}
    /DISCARD/ :
    {{
        *(*);
    }}
}}
"""


def objects(n: str, r: dict[str, Any]) -> list[str]:
    objs = [f"build/src/mod/{n}.c.o"]
    if pool_start(n, r) < r["text"]:
        objs.append(f"build/asm/data/mod/{n}_pool.rodata.s.o")
    if r["data"]:
        objs.append(f"build/asm/data/mod/{n}.data.s.o")
    return objs


def write_ld(n: str, r: dict[str, Any]) -> None:
    pool = f"        build/asm/data/mod/{n}_pool.rodata.s.o(.rodata);\n" if pool_start(n, r) < r["text"] else ""
    data = f"        build/asm/data/mod/{n}.data.s.o(.data);\n" if r["data"] else ""
    # every function start also answers to <name>_<VRAM>: C calls a module function by that name when the
    # compiler must not see its definition (a static callee's C changes the caller's code; dk try knows the name)
    starts = sorted({p.stem.split("_")[1] for k in ("nonmatchings", "matchings")
                     for p in (ROOT / f"asm/{k}/mod/{n}").glob(f"func_*_{n}.s")})
    aliases = "".join(f"{n}_{a} = 0x{a};\n" for a in starts) + ("\n" if starts else "")
    # a jump table in the literal pool names its targets by the asm's labels (.word .L<VRAM>_<n>); once the
    # function is C those labels are gone, so they also answer to their addresses (PROVIDE: the asm's own wins)
    pool_s = ROOT / f"asm/data/mod/{n}_pool.rodata.s"
    labels = sorted(set(re.findall(rf"\.word (\.L([0-9A-F]{{8}})_{n})\b", pool_s.read_text()))) if pool else []
    aliases += "".join(f"PROVIDE({s} = 0x{a});\n" for s, a in labels) + ("\n" if labels else "")
    (ROOT / f"linker/mod/{n}.ld").write_text(LD.format(n=n, pool=pool, data=data, aliases=aliases))


def write_mk(table: dict[str, dict[str, Any]]) -> None:
    """linker/mod/modules.mk: each module ELF's objects (the Makefile includes it)"""
    lines = [f"$(BUILD)/modules/{n}.elf: {' '.join(objects(n, r))}\n" for n, r in sorted(table.items())]
    (ROOT / "linker/mod/modules.mk").write_text("".join(lines))


def section(elf: Path, name: str) -> bytes:
    """the bytes of one ELF section (empty if the section is not there or is NOBITS)"""
    out = elf.with_suffix(f".{name.strip('.')}.bin")
    r = subprocess.run(["mipsel-none-elf-objcopy", "-O", "binary", "--only-section", name, str(elf), str(out)],
                       capture_output=True)
    data = out.read_bytes() if r.returncode == 0 and out.exists() else b""
    out.unlink(missing_ok=True)
    return data


def pack(name: str, elf: Path, out: Path) -> None:
    r = read_table()[name]
    text, data = section(elf, ".text"), section(elf, ".data")
    hdr = HEADER.pack(b"MWo3", r["slot"], r["entry"], len(text), len(data), r["bss"], r["cb_start"], r["cb_end"],
                      f"{name}.bin".encode().ljust(32, b"\0"), bytes(64))
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(hdr + text + data)


def check(names: list[str]) -> None:
    table = read_table()
    names = names or sorted(table)
    bad = []
    for n in names:
        f = ROOT / "build/modules" / f"{n}.mwo"
        if not f.exists() or hashlib.sha1(f.read_bytes()).hexdigest() != table[n]["sha1"]:
            bad.append(n)
    if bad:
        sys.exit(f"modules: {len(bad)} of {len(names)} differ from the disc: {' '.join(bad[:12])}"
                 f"{' ...' if len(bad) > 12 else ''}")
    print(f"OK: {len(names)} modules match the disc")


if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else ""
    if cmd == "extract":
        extract()
    elif cmd == "split":
        split(only=sys.argv[2:] or None)
    elif cmd == "ld":
        table = read_table()
        for n in sys.argv[2:] or sorted(table):
            write_ld(n, table[n])
    elif cmd == "pack":
        pack(sys.argv[2], Path(sys.argv[3]), Path(sys.argv[4]))
    elif cmd == "check":
        check(sys.argv[2:])
    else:
        sys.exit(__doc__)
