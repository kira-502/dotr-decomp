#!/usr/bin/env python3
"""tools/perm/mix.py FUNC FILE --decl LO-HI [--add "s32 l;" ...] [--jobs N] [--max M] SPEC...
Random search mixing section renames (SPEC = LO-HI:v1,v2=p1,p2,..., as in renames.py) with a shuffled declaration
block (lines LO-HI of FILE, plus any --add lines). Scored by tools/perm/fastscore.py; best -> FILE.mix.c.
Line numbers refer to FILE as given (renames are applied before the declaration block is rebuilt)."""
import os, random, re, sys
from multiprocessing import Pool
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fastscore
a = sys.argv[1:]
def opt(name, default, conv=str, multi=False):
    vals = []
    while name in a:
        i = a.index(name); vals.append(conv(a[i + 1])); del a[i:i + 2]
    return vals if multi else (vals[-1] if vals else default)
jobs, mx = opt('--jobs', 5, int), opt('--max', 3000, int)
drange, adds = opt('--decl', None), opt('--add', None, multi=True)
func, wf, specs = a[0], a[1], a[2:]
lines = open(wf).read().split('\n')
dlo, dhi = map(int, drange.split('-'))
S = []
for sp in specs:
    rng, rest = sp.split(':'); lo, hi = map(int, rng.split('-')); vs, pool = rest.split('=')
    S.append((lo, hi, vs.split(','), pool.split(',')))
def build(c):
    picks, order = c
    out = list(lines)
    for (lo, hi, vs, pool), pick in zip(S, picks):
        mp = dict(zip(vs, pick)); pat = re.compile(r'(?<![\w.>])(%s)\b' % '|'.join(map(re.escape, vs)))
        for i in range(lo - 1, hi): out[i] = pat.sub(lambda m: mp[m.group(1)], out[i])
    return '\n'.join(out[:dlo - 1] + order + out[dhi:])
decl = lines[dlo - 1:dhi] + ['    ' + x for x in adds]
def rand():
    return (tuple(tuple(random.sample(pool, len(vs))) for lo, hi, vs, pool in S), random.sample(decl, len(decl)))
def job(c): return fastscore.score(func, build(c)), c
if __name__ == '__main__':
    base = fastscore.score(func, open(wf).read()); print('base', base, flush=True)
    best = base; res = []
    with Pool(jobs) as p:
        for sc, c in p.imap_unordered(job, [rand() for _ in range(mx)], chunksize=2):
            res.append(sc)
            if sc < best:
                best = sc; print(sc, c[0], [x.strip() for x in c[1]], flush=True); open(wf + '.mix.c', 'w').write(build(c))
    res.sort(); print('dist', res[:20]); print('best', best)
