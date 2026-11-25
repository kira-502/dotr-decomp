#!/usr/bin/env python3
"""tools/perm/decls.py FUNC FILE [--jobs N] [--max M] "decl;" "decl;" ...
Every order of the given declaration lines (exact text without indentation, e.g. "f32 t0;"), re-inserted as a block
where the first of them stood, scored in parallel by tools/perm/fastscore.py (instruction diff against
build/try/FUNC/FUNC.target.o; run dk try once first). More than M orders (default 5040): a random sample of M.
Prints improvements; best version -> FILE.dp.c. Toolchain env must be loaded."""
import itertools
import os
import random
import sys
from multiprocessing import Pool

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fastscore  # noqa: E402

args = sys.argv[1:]
jobs, mx = 4, 5040
if '--jobs' in args:
    i = args.index('--jobs'); jobs = int(args[i + 1]); del args[i:i + 2]
if '--max' in args:
    i = args.index('--max'); mx = int(args[i + 1]); del args[i:i + 2]
func, wf, decls = args[0], args[1], args[2:]
lines = open(wf).read().split('\n')
idx = [next(i for i, l in enumerate(lines) if l.strip() == d) for d in decls]
first = min(idx)
indent = lines[first][:len(lines[first]) - len(lines[first].lstrip())]
rest = [l for i, l in enumerate(lines) if i not in idx]
pos = first - sum(1 for i in idx if i < first)


def build(order):
    return '\n'.join(rest[:pos] + [indent + d for d in order] + rest[pos:])


def job(order):
    return fastscore.score(func, build(order)), order


if __name__ == '__main__':
    base = fastscore.score(func, open(wf).read())
    print('base', base, flush=True)
    n = len(decls)
    total = 1
    for k in range(2, n + 1):
        total *= k
    if total <= mx:
        orders = list(itertools.permutations(decls))
    else:
        orders = [tuple(random.sample(decls, n)) for _ in range(mx)]
    best = base
    with Pool(jobs) as p:
        for sc, order in p.imap_unordered(job, orders, chunksize=4):
            if sc < best:
                best = sc
                print(sc, ' '.join(order), flush=True)
                open(wf + '.dp.c', 'w').write(build(order))
    print('best', best)
