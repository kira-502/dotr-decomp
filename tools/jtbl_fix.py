#!/usr/bin/env python3
"""Point each decompiled function's switch jump table at the game's own table.

Metrowerks gives every function its own .rodata section for its jump table and
loads the table through a local symbol (`@9`). In the game those tables sit in
the data blob (asm/data/data.data.s, labels jtbl_XXXXXXXX) as plain addresses,
which stay right as long as the code matches. So the compiled table is not
needed: each table symbol becomes an absolute symbol named after the original
table (taken, in order, from the function's asm file), and the compiled table's
section is renamed so the linker script's /DISCARD/ drops it.
GCC files (config/gcc_files.txt) get the same on GCC's assembly, before it is assembled:
GCC writes each table into .rdata (`$L19: .word $L14 ...`), which the linker script drops
for every file, and loads it with %hi/%lo($L19) (2.9) or the macro `lw $3,$L19($2)` (2.96). The loads get the original table's name
(the function's Nth table = the Nth jtbl_ in its asm) and the compiled table goes.
Usage: jtbl_fix.py object.o   (run from the project root, after pad_functions.py)
       jtbl_fix.py --gcc out.s   (GCC's assembly, from the project root)"""
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(os.environ["DK_TOOLCHAIN"]) / "src/mwccgap"))
from mwccgap.elf import Elf, TextSection  # noqa: E402

JTBL_RE = re.compile(r"%hi\((jtbl_[0-9A-Fa-f]{8}(?:_\w+)?)\)")
R_MIPS_HI16 = 5
SHN_ABS = 0xFFF1
SHF_ALLOC = 0x2
DROPPED = ".jtbl_compiled"
GCC_LABEL_RE = re.compile(r"^(\$L\d+):")
GCC_REF_RE = re.compile(r"%(hi|lo)\((\$L\d+)\)")
GCC_MEM_RE = re.compile(r"(?<=,)(\$L\d+)(?=\()")  # 2.96's macro form: `lw $3,$L170($2)`


def fix_gcc(path: Path) -> None:
    lines = path.read_text().splitlines(keepends=True)
    section = ".text"
    tables = {}  # table label -> number of .word lines after it
    for i, line in enumerate(lines):
        words = line.split()
        if words[:1] in ([".text"], [".rdata"], [".data"], [".section"]):
            section = words[0] if words[0] != ".section" else words[1].rstrip(",")
        m = GCC_LABEL_RE.match(line)
        if m and section == ".rdata":
            n = 0
            while i + 1 + n < len(lines) and lines[i + 1 + n].split()[:1] == [".word"]:
                n += 1
            if n:
                tables[m.group(1)] = n
    if not tables:
        return
    used = {}  # function -> its table labels, in order of first use
    func = None
    for line in lines:
        words = line.split()
        if words[:1] == [".ent"]:
            func = words[1]
        for label in [r[1] for r in GCC_REF_RE.findall(line)] + GCC_MEM_RE.findall(line):
            if label in tables and label not in used.setdefault(func, []):
                used[func].append(label)
    names = {}
    for func, labels in used.items():
        asm = next(Path("asm").glob(f"**/{func}.s"), None)
        if asm is None:  # not a game function (a scratch file): keep GCC's table
            continue
        originals = list(dict.fromkeys(JTBL_RE.findall(asm.read_text())))
        if len(originals) != len(labels):
            sys.exit(f"jtbl_fix: {func} has {len(labels)} switch table(s), its asm uses {len(originals)}")
        names.update(zip(labels, originals))
    out = []
    skip = 0
    for line in lines:
        if skip:
            skip -= 1
            continue
        m = GCC_LABEL_RE.match(line)
        if m and m.group(1) in names:
            skip = tables[m.group(1)]
            continue
        line = GCC_REF_RE.sub(lambda r: f"%{r.group(1)}({names.get(r.group(2), r.group(2))})", line)
        out.append(GCC_MEM_RE.sub(lambda r: names.get(r.group(1), r.group(1)), line))
    path.write_text("".join(out))


if sys.argv[1] == "--gcc":
    fix_gcc(Path(sys.argv[2]))
    sys.exit(0)

path = Path(sys.argv[1])
elf = Elf(path.read_bytes())
names = {}
for symbol in elf.symtab.symbols:
    if symbol.type == 2 and not symbol.name.endswith(".NON_MATCHING"):  # STT_FUNC
        names.setdefault(symbol.st_shndx, symbol.name)

changed = False
for record in elf.get_relocations():
    target = record.sh_info
    func = names.get(target)
    if func is None or not isinstance(elf.sections[target], TextSection):
        continue
    tables = []  # table symbol indexes, in order of first use
    for reloc in sorted(record.relocations, key=lambda r: r.r_offset):
        if reloc.reloc_type != R_MIPS_HI16:
            continue
        symbol = elf.symtab.symbols[reloc.symbol_index]
        shndx = symbol.st_shndx
        if (symbol.bind == 0 and symbol.name.startswith("@") and 0 < shndx < len(elf.sections)
                and elf.sections[shndx].name == ".rodata" and reloc.symbol_index not in tables):
            tables.append(reloc.symbol_index)
    if not tables:
        continue
    asm = next(Path("asm").glob(f"**/{func}.s"), None)
    if asm is None:  # not a game function (a scratch file): nothing to point at
        continue
    originals = list(dict.fromkeys(JTBL_RE.findall(asm.read_text())))
    if len(originals) != len(tables):
        sys.exit(f"jtbl_fix: {func} has {len(tables)} switch table(s), its asm uses {len(originals)}")
    for index, original in zip(tables, originals):
        symbol = elf.symtab.symbols[index]
        section = elf.sections[symbol.st_shndx]
        section.sh_flags &= ~SHF_ALLOC
        section.sh_name = elf.add_sh_symbol(DROPPED)
        section.name = DROPPED
        symbol.name = original
        symbol.st_name = elf.strtab.add_symbol(original)
        symbol.st_shndx = SHN_ABS
        symbol.st_value = int(original[5:13], 16)
        changed = True
if changed:
    path.write_bytes(elf.pack())
