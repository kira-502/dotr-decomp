#!/usr/bin/env python3
"""fastscore.py: parallel-safe scoring of single-function drafts against build/try/<func>/<func>.target.o
(run `dk try <func> <file>` once first so the target object exists). Needs the toolchain env loaded.

  python3 tools/perm/fastscore.py FUNC FILE...      prints "<differing instructions> <file>" per file

As a module: score(func, src_text) -> differing-instruction count (difflib opcode diff of the disassembly,
lower is better; 0 = same instructions, relocation names ignored); 99999 on a compile failure.
Used by tools/perm/decls.py and renames.py (parallel declaration-order search)."""
import difflib
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
_TGT = {}


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


def target(func):
    if func not in _TGT:
        _TGT[func] = dis(os.path.join(ROOT, 'build/try', func, func + '.target.o'), func)
    return _TGT[func]


def score(func, src):
    d = tempfile.mkdtemp(prefix='fs_')
    c = os.path.join(d, func + '.c')
    o = os.path.join(d, func + '.o')
    open(c, 'w').write(src)
    env = dict(os.environ, DK_WARM='1')
    r = subprocess.run(['bash', os.path.join(ROOT, 'tools/cc.sh'), c, o], cwd=ROOT, env=env,
                       capture_output=True, text=True)
    if r.returncode != 0 or not os.path.exists(o):
        subprocess.run(['rm', '-rf', d])
        return 99999
    mine = dis(o, func)
    subprocess.run(['rm', '-rf', d])
    t = target(func)
    sm = difflib.SequenceMatcher(None, t, mine, autojunk=False)
    same = sum(b.size for b in sm.get_matching_blocks())
    return max(len(t), len(mine)) - same


if __name__ == '__main__':
    func = sys.argv[1]
    for f in sys.argv[2:]:
        print(score(func, open(f).read()), f, flush=True)
