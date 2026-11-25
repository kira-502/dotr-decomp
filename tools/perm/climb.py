#!/usr/bin/env python3
"""tools/perm/climb.py FUNC FILE --decl LO-HI [--add "s32 l;"]... [--minutes M] [--jobs N] SPEC...
Hill climb (sideways moves allowed) over a declaration order plus per-section renames (SPEC as in renames.py; each
section's variables are renamed injectively to pool variables). Each round mutates the current state N ways in
parallel: swap two declarations, or re-pick one section's names. Best -> FILE.climb.c. Scored by fastscore."""
import os, random, re, sys, time
from multiprocessing import Pool
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fastscore
a = sys.argv[1:]
def opt(name, default, conv=str, multi=False):
    vals = []
    while name in a:
        i = a.index(name); vals.append(conv(a[i + 1])); del a[i:i + 2]
    return vals if multi else (vals[-1] if vals else default)
jobs, minutes = opt('--jobs', 5, int), opt('--minutes', 60, float)
drange, adds = opt('--decl', None), opt('--add', None, multi=True)
func, wf, specs = a[0], a[1], a[2:]
lines = open(wf).read().split('\n')
dlo, dhi = map(int, drange.split('-'))
S = []
for sp in specs:
    rng, rest = sp.split(':'); lo, hi = map(int, rng.split('-')); vs, pool = rest.split('=')
    S.append((lo, hi, vs.split(','), pool.split(',')))
def build(st):
    picks, order = st
    out = list(lines)
    for (lo, hi, vs, pool), pick in zip(S, picks):
        mp = dict(zip(vs, pick)); pat = re.compile(r'(?<![\w.>])(%s)\b' % '|'.join(map(re.escape, vs)))
        for i in range(lo - 1, hi): out[i] = pat.sub(lambda m: mp[m.group(1)], out[i])
    return '\n'.join(out[:dlo - 1] + list(order) + out[dhi:])
def mutate(st):
    picks, order = list(st[0]), list(st[1])
    if S and random.random() < 0.5:
        k = random.randrange(len(S)); lo, hi, vs, pool = S[k]
        picks[k] = tuple(random.sample(pool, len(vs)))
    else:
        i, j = random.sample(range(len(order)), 2); order[i], order[j] = order[j], order[i]
    return (tuple(picks), tuple(order))
def job(st): return fastscore.score(func, build(st)), st
if __name__ == '__main__':
    cur = (tuple(tuple(vs) for lo, hi, vs, pool in S), tuple(lines[dlo - 1:dhi] + ['    ' + x for x in adds]))
    cs = fastscore.score(func, build(cur)); best = cs; print('start', cs, flush=True)
    end = time.time() + minutes * 60; rounds = 0
    with Pool(jobs) as p:
        while time.time() < end and best > 0:
            rounds += 1
            for sc, st in p.map(job, [mutate(cur) for _ in range(jobs)]):
                if sc <= cs:
                    cur, cs = st, sc
                if sc < best:
                    best = sc; print(rounds, sc, st[0], [x.strip() for x in st[1]], flush=True)
                    open(wf + '.climb.c', 'w').write(build(st))
    print('rounds', rounds, 'best', best)
