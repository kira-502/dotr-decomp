#!/usr/bin/env python3
"""tools/perm/check.py DIR FUNC [SRC]: differing-instruction count of DIR/base.c (or SRC) compiled by DIR/compile.sh vs DIR/target.o."""
import sys, subprocess, difflib, os
import re


def dis(obj, func):
    out = subprocess.run(['mipsel-none-elf-objdump', '-d', '-M', 'no-aliases', '--disassemble=' + func, obj],
                         capture_output=True, text=True).stdout
    ins = []
    for ln in out.split('\n'):
        m = re.match(r'^\s+[0-9a-f]+:\t[0-9a-f]+ \t(.*)$', ln)
        if m:
            t = re.sub(r'\s+', ' ', m.group(1)).strip()
            t = re.sub(r'<[^>]*>', '', t).strip()
            ins.append(t)
    return ins


d, func = sys.argv[1], sys.argv[2]
src = sys.argv[3] if len(sys.argv) > 3 else d + "/base.c"
o = "/var/tmp/permcheck.%d.o" % os.getpid()
r = subprocess.run([d + "/compile.sh", src, "-o", o], capture_output=True, text=True)
if r.returncode:
    print("compile failed"); print(r.stdout[-2000:]); sys.exit(1)
a, b = dis(o, func), dis(d + "/target.o", func)
print(len(a), len(b), sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in
      difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes() if t != "equal"))
for x in (o, o + ".d"):
    if os.path.exists(x): os.unlink(x)
