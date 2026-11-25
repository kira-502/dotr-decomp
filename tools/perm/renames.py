#!/usr/bin/env python3
"""tools/perm/renames.py FUNC FILE [--jobs N] [--max M] SPEC...
SPEC = LO-HI:v1,v2,...=p1,p2,...  : in lines LO..HI (1-based) of FILE, rename each of v1,v2,.. to a distinct
variable from the pool p1,p2,.. (the vi themselves included if listed). All combinations across SPECs (random
sample of M if more), scored in parallel by tools/perm/fastscore.py . Improvements printed; best -> FILE.rp.c."""
import itertools, os, random, re, sys
from multiprocessing import Pool
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fastscore

args = sys.argv[1:]
jobs, mx = 5, 3000
if '--jobs' in args:
    i = args.index('--jobs'); jobs = int(args[i + 1]); del args[i:i + 2]
if '--max' in args:
    i = args.index('--max'); mx = int(args[i + 1]); del args[i:i + 2]
func, wf, specs = args[0], args[1], args[2:]
lines = open(wf).read().split('\n')
S = []
for sp in specs:
    rng, rest = sp.split(':')
    lo, hi = map(int, rng.split('-'))
    vs, pool = rest.split('=')
    S.append((lo, hi, vs.split(','), pool.split(',')))
choices = [list(itertools.permutations(pool, len(vs))) for lo, hi, vs, pool in S]


def build(combo):
    out = list(lines)
    for (lo, hi, vs, pool), pick in zip(S, combo):
        mp = dict(zip(vs, pick))
        pat = re.compile(r'(?<![\w.>])(%s)\b' % '|'.join(map(re.escape, vs)))
        for i in range(lo - 1, hi):
            out[i] = pat.sub(lambda m: mp[m.group(1)], out[i])
    return '\n'.join(out)


def job(combo):
    return fastscore.score(func, build(combo)), combo


if __name__ == '__main__':
    base = fastscore.score(func, open(wf).read())
    print('base', base, flush=True)
    total = 1
    for c in choices:
        total *= len(c)
    combos = list(itertools.product(*choices)) if total <= mx else \
        [tuple(random.choice(c) for c in choices) for _ in range(mx)]
    print(len(combos), 'combos of', total, flush=True)
    best = base
    res = []
    with Pool(jobs) as p:
        for sc, combo in p.imap_unordered(job, combos, chunksize=2):
            res.append((sc, combo))
            if sc < best:
                best = sc
                print(sc, combo, flush=True)
                open(wf + '.rp.c', 'w').write(build(combo))
    res.sort()
    print('top:', res[:8])
    print('best', best)
