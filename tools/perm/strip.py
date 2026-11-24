#!/usr/bin/env python3
"""tools/perm/strip.py DIR FUNC: cut a dk perm directory's base.c down to FUNC, its callees (transitively: MWCC inlines some
and reads the others' bodies when compiling FUNC), inline functions and PERM macros; other bodies become prototypes
the #pragmas in force at FUNC move to the top (the rest go), and the layout checks go. Run the permuter through tools/perm/run.py, which keeps those bodies.
Why: a draft that includes its module file compiles every module function, and the permuter's AST regeneration moves
the pragmas onto the wrong declarations. Keeps the original as base.full.c."""
import re, sys
from pathlib import Path

def bracket_end(s, i):
    lvl = 0
    while True:
        lvl += {"{": 1, "}": -1}.get(s[i], 0)
        if lvl == 0:
            return i
        i += 1

FN = re.compile(r"^[^\n;{}#]*?\s\**(\w+)\s*\([^;{}]*\)\s*\{", re.M)

def bodies(src):
    out, i = {}, 0
    while (m := FN.search(src, i)):
        end = bracket_end(src, m.end() - 1)
        out[m.group(1)] = src[m.end():end]
        i = end + 1
    return out

def needed(src, keep):
    """FUNC's callees, transitively: MWCC inlines some and reads the others' bodies when compiling FUNC."""
    b, todo, seen = bodies(src), [keep], set()
    while todo:
        f = todo.pop()
        if f in seen or f not in b:
            continue
        seen.add(f)
        todo += re.findall(r"\b(\w+)\s*\(", b[f])
    return seen

def strip(src, keep):
    out, rest, fn, want = [], src, FN, needed(src, keep)
    while (m := fn.search(rest)):
        end = bracket_end(rest, m.end() - 1)
        head = rest[m.start():m.end() - 1]
        if m.group(1) in want or m.group(1).startswith("PERM") or re.search(r"\binline\b", head):
            out.append(rest[:end + 1])
        else:
            out.append(rest[:m.end() - 1].rstrip() + ";")
        rest = rest[end + 1:]
    out.append(rest)
    src = "".join(out)
    # the pragmas in force at FUNC (a set before it and not reset) go to the top: only FUNC is scored
    top, on = [], {}
    pos = [m for m in FN.finditer(src) if m.group(1) == keep][0].start()
    for m in re.finditer(r"^#pragma\s+(\w+)\s+(.*)$", src[:pos], re.M):
        if m.group(2).strip() == "reset":
            on.pop(m.group(1), None)
        else:
            on[m.group(1)] = m.group(0)
    src = re.sub(r"^#pragma.*\n", "", src, flags=re.M)
    # game.h layout checks (when cpp did not define __MWERKS__): mwcc and the permuter's parser reject them
    src = re.sub(r"^.*__builtin_offsetof.*\n", "", src, flags=re.M)
    return "".join(v + "\n" for v in on.values()) + src

d, func = Path(sys.argv[1]), sys.argv[2]
full = d / "base.full.c"
if not full.exists():
    full.write_text((d / "base.c").read_text())
(d / "base.c").write_text(strip(full.read_text(), func))
