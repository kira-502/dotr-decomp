# Matching tips for the code modules

What made module functions match, gathered from the matches so far (most recent round: 25 October 2026). Each tip:
the **tell** (what the diff shows), the **fix**, and a function it closed. Add yours at the end.

The compiler is Metrowerks CodeWarrior for PS2 2.3.3 (build 000906), `-O4,p -sdatathreshold 0 -relax_pointers`
unless a function says otherwise. It decides with rules, not chance: when one register or one instruction is off,
there is a source form that gives the original.

## How this compiler decides (the rules behind most fixes)

- **Register colouring.** 26 allocatable registers. Cheap webs that cross calls (flags, offsets, arguments used
  once) get registers last; everything else goes in descending virtual-register order, each to the lowest free
  register. Virtual-register order: split webs < `?:` temporaries < declared locals, and among declared locals the
  first declared is the highest. So: to give a value an earlier (lower-numbered) saved register, make it a named
  local declared earlier; to push it later, declare it later or reuse a variable from an earlier block.
- **Parameters colour last.** A context pointer the original keeps in `$s0` while yours lands in a high
  s-register is a local copy in the source: take the parameter as `s32 arg0` and write `Ctx *g = (Ctx *)arg0;` as
  the first local (or `T *g = (T *)(u32)g0;`).
- **Code-generation temporaries** are numbered in the order the statements create them; a temp created later gets
  a higher number and its register first. Moving one statement below another swaps two registers.
- **The scheduler runs twice**: before allocation (smallest change in live registers first, ties in source order)
  and after it. Call arguments are evaluated left to right; to load one earlier, make it its own statement.
- **Delay slots.** A branch's delay slot is filled by copying the target's first instruction. The same address
  computed twice (once in a slot, once at the join) is one statement placed right after the `if`.
- **Carried state.** The compiler keeps some memory from one function to the next in the same file, so a function
  can compile differently depending on what came before it. `dk try` compiles your function alone and then in its
  file; `dk accept` and `make check` build the real file. When the two disagree, the real file wins.
- **Per-function settings exist and are honest C:** `#pragma optimization_level 1|2|3`, `opt_propagation off`,
  `conditional_move off`, `opt_strength_reduction off`, `global_optimizer off`, `peephole off`, `schedule off`.
  Put the pragma before the function and `#pragma <name> reset` after it. When nothing else moves a difference, try
  them one at a time.

## Module basics

- **`static`.** Every module function is static. Without it the accept adds a prototype to `include/functions.h`
  and the module file fails with "identifier expected".
- **Tables are module data.** Tell: `lui %hi(@34)` where the original has `lui %hi(D_01E06480_b000)`. A local
  `T tbl[4] = {{...}}` makes the compiler emit its own copy; the original copies the module's data. Fix:
  `typedef struct { T v[4]; } Tbl; extern Tbl D_01E06480_b000; Tbl tbl = D_01E06480_b000;` then `tbl.v[i]`.
  Closed LkSetLight (b000:01E032C0) and 67 copies, then about 180 more.
- **Other functions of the same module** are called by their link name `<module>_<VADDR>` through a block-scope
  `extern s32 b708_01E01610();` (no prototype), unless they are static and defined earlier in the file: then call
  them by their real name. Pass the arguments the asm shows, even unused ones.
- **Flag sets.** All delay slots `nop` + `addiu sp` before `jr ra` + u8 locals masked on every read = `-O2,p`;
  the same but every field reloaded in each statement = `-O1,p`; `x == 5 || x == 6` kept as two compares = `-O3,p`.
  If `dk try` suggests `optimization_level 0`, try 1 first: saved registers and no argument spills mean -O1.
  Same-named functions in other modules are often the same C built with other flags.
- **Copies.** One shape in many modules is one C file. After a match, `python3 tools/mod_spread.py <func> --consts`.

## Clashes (`dk try` says CLASH)

- A module global that an earlier function in the file already declares with its own type: add
  `#include "mod/b136.c"` under `#include "common.h"` and use the file's own names; `dk try` finds it through
  `-I src`, and the accept drops `#include` lines. (b136:01E019D0)
- A typedef name the module file already has: rename yours with the shape id suffix.
- To see the real error: `dk try` leaves the placed file in `build/try/<func>/proj/src/mod/<module>.c`; compile it
  with `DK_WARM=1 tools/cc.sh <that file> /tmp/x.o`.
- `dk draft` fails with a syntax error on `__builtin_offsetof(...)`: m2c cannot read the layout checks at the end
  of `include/game.h`. Draft with a copy of the headers that leaves those lines out.

## Registers

- **Leaf temporaries: write the temp after the loads it must outrank.** Leaf functions colour every value in one
  cascade. `t = s + k * s;` before `p->v[2].r = c->r;` swapped two registers; moving it right before its first use
  matched. (c555:01E00120)
- **A constant argument loaded in the wrong order:** `f(quad, 3.0f, o->len)` loads len first; the original loads
  the constant first. `w = 3.0f;` as its own statement before the call, under `#pragma opt_propagation off` (else
  the copy folds back). (b089:01E04770, c056:01E04CF0)
- **A quotient in the divisor's FPR** (`div.s f1,f2,f1` vs `f2,f2,f1`): a float local, `r = o->rise; r /= 10.0f;`.
- **A float constant held in a saved FPR across calls** (`mtc1 $zero, $f20` once, then `mul.s` after each call):
  `#pragma opt_propagation off` around the function; if the loop then gains a top test, write it `do { } while`.
  (b120:01E03B30)
- **Two loops, wrong counters.** Each variable name is one colour choice across all its loops. Try: one `i` for
  every loop; a separate counter per loop; swapping which name each loop uses; declaration-order permutations
  (script them). (b034:01E06010, b516:01E01CF0, b481:01E020F0)
- **A counter that is s32 in one loop and s16 in another:** `s32 n;` and `n = (s16)(n + 1);`. (b278:01E01230)
- **A value counted but never read** (`addiu sN, sN, 1` in a draw loop with no use): it is real; keep `n = 0;` /
  `n++;` in the source. (b086:01E01290)
- **`&local` in a saved register across a call:** assign the pointer inside the call's argument list,
  `f(..., p = (f32 *)(u32)b);`, then read through `p`. (b008:01E00A50, b572:01E019E0)
- **Slot finders:** assign the slot pointer last: `clear(&m->ents[i], 0x94); m->ents[i].active = i + 1;
  e = &m->ents[i];`. (c021:01E028F0)

## Compares and branches

- **`slti $at` vs `slti $v0/$v1`.** `x > K-1` gives `slti $at, x, K; bnez $at`; `x >= K` gives `slti $v1, x, K;
  bnez $v1`. Read the destination register of the original's compare and write the matching form. Same for
  `< K` / `<= K-1`. Fixed dozens of functions. (b202:01E01A80, b552:01E01240, b570:01E016C0)
- **Operand order of a compare:** `if (r[1] > o->a)` and `if (o->a < r[1])` load in different orders.
  (c059:01E006D0)
- **`if (c)` vs `if (c != 0)` on an s16:** the second re-extends the value (two extra instructions). (b206:01E01DB0)
- **An extra sign extension of an already-s16 load** (`dsll32/dsra32` right after `lh`) = an `(s16)` cast in the
  source. (b520:01E01230)
- **Both arms equal:** `if (x < 100) n = 3; else n = 3;` is real code; the compiler keeps both.
- **A missing `nop` before the epilogue** = if/else, not an early `return;`. (c030:01E02170, c031:01E01950)
- **A duplicated instruction in a branch delay slot** = the statement after the `if`. (c030:01E01110)
- **u8 times float with a `bgez ... cvt.s.w` / `2 * cvt(...)` pair** = a `(u32)` cast on the u8. (c021:01E03390)
- **A clamp whose result is stored without a final extension:** an inline helper returning `u8`.
  (b256:01E04AB0)

## Stack and frames

- **Frame 0x10 too big or too small, everything else equal:** the local is bigger than the code uses. Common: the
  out buffer of `func_001F5620` is two vectors (`Vec4f t[2]`); `func_00208800`'s second out parameter is
  `s32 b[3]`; `f32 v[8]` where the code uses `v[0..2]`. (b406:01E01590, b000:01E001A0, b501:01E02370)
- **A buffer at a higher offset than yours:** the code uses its second half (`pv = &v[4]`). (b056:01E01FC0)
- **Spilled parameters 4 bytes off:** `__attribute__((aligned(8)))` on the first spilled parameter (or
  `aligned(16)` when it sits alone in its own 16-byte chunk). (b024:01E02120, b029:01E02B80)
- **`x *= -1` keeps direct stack offsets where `x = -x` makes an address temp.** (b053:01E00080)
- **A 16-byte struct returned by value into a field:** go through a named local per call site.
- **Field stores through `addiu sN, sp, ..` set once at entry:** member pointers (`py = &pos.y; *py = ...`).
- **A struct passed by value to a sibling:** give that extern a prototype and pass a local copy.

## Calls and siblings

- **Missing argument reloads after a call to a static function defined above you** (`paddub a0, sN` absent,
  or `addiu a1/a3` not repeated): not your bug. In the real file the compiler knows the callee leaves those
  registers alone. Check with `tools/mod_infile.sh <func> <file>` or `dk accept`. (b516:01E02AC0, b582:01E04E60)
- **A draw call whose last store left the `jal` delay slot:** call the main-program function unprototyped,
  `extern s32 func_00205630(); func_00205630(q, 0x70000000, m, pkt, ctx + 0x36FC);`. (b774:01E03860)
- **Float to int:** write the cast (`(s32)f`, `(u32)f`); module files compile "warm", so the compiler emits the
  runtime call itself. Explicit `func_001A22C0(...)` calls give other registers.

## Families seen many times

- **Scene managers** (`code >= 0` sets up, else step + draw loops): copy a matched twin's skeleton exactly:
  `static s32 f(s32 arg0, s32 code) { Ctx *g = (Ctx *)arg0;` first, then `n, pos, pkt, draw, i`, `n = 0` before the
  ordering-table call, one `i` for every loop. Find twins with `grep -n "draw(g, &g->slot\[i\], pkt, 0)"
  src/mod/c*.c`. (c027:01E00660, b580:01E01B70, c541:01E02C40)
- **`*_W_S` scene scripts:** a timer `g->t++` and a list of `if (g->t == N) spawn(g, fn, 0);` blocks: write them
  straight from the asm, top to bottom. (b703, b747, b286)
- **`*_OBJ_MOVE_*` steps:** the same-named function in another module is usually 99% the same C with other offsets.

## Twins built with other flags (26 October 2026)

- **Find them by their calls.** A still-asm shape whose calls into the main program, in order, are exactly those
  of a finished function is very often the same C at another level (`-O1`/`-O2`/`-O3`/`-O4`), even when the two
  differ by 100+ instructions. Copy the finished C, rename the module labels, try each level. Closed ShFx_Flear01
  (b051:01E003A0 at -O3 = b035:01E00410 at -O2), ShFx_Ndl (b532:01E00080 = b011:01E04380's source at -O2),
  ShFx_Smk01 (b010:01E00410, b029:01E003A0), ShFx_RingTX (b561:01E02A90, b715:01E003A0).
- **What still differs is usually small and mechanical:**
  - spilled parameters 4 bytes off at the new level: `aligned(8)` on the parameter (above, "Stack and frames");
  - tuned constants (`% 50 + 20` there, `% 150 + 30` here; `15.0f` / `10.0f`). A constant written several times
    in the C is loaded once, so change every occurrence together. (b765:01E037A0, B270_OBJ_MOVE_10_)
  - one address computed before another (`addiu a1, sp, &td.w` first): an expression through a local,
    `s32 h = (td.w - td.u) >> 1; td.u += h;`. (b561:01E02A90)
- **`B*_OBJ_MOVE_*` spark trails (b445 family):** `addiu $a0, $sN, 0x5CA0` where yours has `0x5F58` and nothing
  else differs: the world's sine table (`w->trig`, `func_00108030`'s first argument) sits at another offset in each
  module. Give the copy its own world type with the table moved by the difference. (b764:01E035C0, b764:01E02FC0)
- **Float temporaries one register off after the port, every declaration order tried by hand:** `dk perm
  <func> --minutes 15` found the order in one run; copy back only its declaration order, not its reformatted
  body. (b070:01E003A0)
- **Two parameter copies (`paddub sN, aN`) in the other order, nothing else different, before a float-to-int
  conversion:** the original called `func_001A22C0(...)` by name there (`extern s32 func_001A22C0(f32);`); the
  `(s32)` cast gives the same call through the runtime name and the scheduler places the copies the other way.
  (b007:01E00120)
- **Ported twins of trails and particles (b108:01E02010 family, `*PAINT_RAIN*`):** the source is the same, but the
  object and scene layouts move: row length (20/50/70 points), where the points sit, which joint comes first,
  colours (often passed halved, `(u8)(c >> 1)`), fade steps. Read the differing offsets off `dk try`'s diff and give
  the copy its own struct. (b116:01E03190, b121:01E021E0, c017:01E02790, b415:01E02A90, c022:01E00F10)
- **Spreading a `-O1`/`-O2`/`-O3` shape:** `tools/mod_spread.py` copies the typedefs and the definition but not the
  `#pragma optimization_level` lines around it, so its copies of such a shape do not match; carry the pragmas over
  to each copy.
- **A local packet buffer at a stack offset that is 8 mod 16, yours at 0 mod 16:** `u8 buf[0x90]
  __attribute__((aligned(8)));` on the local. (b286:01E01520, b505:01E013F0)
- **A `jal` to a static helper where the original has its body:** MWCC inlines only functions marked `inline`;
  write the helper's body out at the call site. (b286:01E01520, b505:01E013F0)
- **A `work/port.py` port scores far below what the donor's likeness suggests:** diff the port against the donor;
  the constant swapping can rewrite an array index (`pts[1]` became `pts[0]`). (b509:01E03790)
- **Scene manager, the draw counter `n` and the code registers swapped:** count the setup loops with `i`, keep
  `n = 0;` at the top for the draw loop. (b636:01E01120)
- **Two neighbouring stack vectors, the original takes `addiu tN, sp, &second` early and reads `.x` through
  `0(tN)`:** declare them as one array, `Vec4f v[2]`. (b353:01E02660)
- **Only scheduling differs before a loop (a float constant's `lui/ori/mtc1` late, the bounds set too early):**
  put the loop-bound setup (`i = 0; last = n - 1;`) right before the loop; a small script that moves one statement
  to every position, or tries every order of a few statements, finds it fast. (b353:01E02660, b734:01E03EC0)
- **Two stores of a chain `a = b = x;` swapped:** the first store is the rightmost target; swap the targets.
  (c017:01E01BF0)
- **A port gives COMPILE ERROR "identifier expected" on its last lines in standalone `dk try`:** it uses types or
  statics defined earlier in its module file; add `#include "mod/<mod>.c"` under `#include "common.h"` and use the
  file's own type names (the accept drops `#include` lines). This is probably why `tools/mod_spread.py` fails on
  such copies. (b481:01E05050, b516:01E03A10, b068:01E00920)
- **One float constant passed several times to a call (`f(p, 0.15f, 0.15f, 0.15f)`) matches alone but not in its
  file (loaded into $f13 and copied to $f12):** put it in a float local, `s = 0.15f; f(p, s, s, s);`.
  (c024:01E00CD0)
- **Two float constant arguments loaded in the other order (`$f13` before `$f12`), no call-site form fixes it:**
  call through a `static inline` wrapper whose body does the pointer cast,
  `func_001033D0((f32 *)g, target, step);`. About 30 still-asm functions make this `func_001033D0` call.
  (c612:01E014B0)
- **A pointer counter in a nested loop kept twice (spilled and in a register), the original keeps no integer
  counter:** index with a counter that runs through both loops and is used anyway (`&g->obj[n]` on the draw
  counter); a dedicated `k++` leaves a dead counter, `i * 24 + j` a multiply. (c024:01E015D0)
- **A local packet buffer at a stack offset that is 8 mod 16, yours at 0 mod 16:** `u8 buf[0x90]
  __attribute__((aligned(8)));` on the local. (b286:01E01520, b505:01E013F0)
- **A `jal` to a static helper where the original has its body:** MWCC inlines only functions marked `inline`;
  write the helper's body out at the call site. (b286:01E01520, b505:01E013F0)
- **A `work/port.py` port scores far below what the donor's likeness suggests:** diff the port against the donor;
  the constant swapping can rewrite an array index (`pts[1]` became `pts[0]`). (b509:01E03790)
- **Scene manager, the draw counter `n` and the code registers swapped:** count the setup loops with `i`, keep
  `n = 0;` at the top for the draw loop. (b636:01E01120)
- **Two neighbouring stack vectors, the original takes `addiu tN, sp, &second` early and reads `.x` through
  `0(tN)`:** declare them as one array, `Vec4f v[2]`. (b353:01E02660)
- **Only scheduling differs before a loop (a float constant's `lui/ori/mtc1` late, the bounds set too early):**
  put the loop-bound setup (`i = 0; last = n - 1;`) right before the loop; a small script that moves one statement
  to every position, or tries every order of a few statements, finds it fast. (b353:01E02660, b734:01E03EC0)
- **Two stores of a chain `a = b = x;` swapped:** the first store is the rightmost target; swap the targets.
  (c017:01E01BF0)
- **A port gives COMPILE ERROR "identifier expected" on its last lines in standalone `dk try`:** it uses types or
  statics defined earlier in its module file; add `#include "mod/<mod>.c"` under `#include "common.h"` and use the
  file's own type names (the accept drops `#include` lines). This is probably why `tools/mod_spread.py` fails on
  such copies. (b481:01E05050, b516:01E03A10, b068:01E00920)
- **One float constant passed several times to a call (`f(p, 0.15f, 0.15f, 0.15f)`) matches alone but not in its
  file (loaded into $f13 and copied to $f12):** put it in a float local, `s = 0.15f; f(p, s, s, s);`.
  (c024:01E00CD0)
- **Two float constant arguments loaded in the other order (`$f13` before `$f12`), no call-site form fixes it:**
  call through a `static inline` wrapper whose body does the pointer cast,
  `func_001033D0((f32 *)g, target, step);`. About 30 still-asm functions make this `func_001033D0` call.
  (c612:01E014B0)
- **A pointer counter in a nested loop kept twice (spilled and in a register), the original keeps no integer
  counter:** index with a counter that runs through both loops and is used anyway (`&g->obj[n]` on the draw
  counter); a dedicated `k++` leaves a dead counter, `i * 24 + j` a multiply. (c024:01E015D0)
- **A new function matches in `dk try` and `tools/mod_infile.sh`, but the accept is REJECTED and an already-matched
  function further down now loads two float constants in the other order:** MWCC orders constant loads by when
  each constant first appears in the file, and the new function uses one of them first (here `5.0f`). Splice by hand
  (`work/splice.py`), build the module and diff it against the disc (`work/moddiff.py`), then change the later
  function's call so both orders give the original: `f32 r = 5.0f;` as a block local and pass `r`. Commit it with the
  new function. (b244:01E02B40 changed func_01E031E0_b244)
- **Two float constant arguments where the first argument's address (`addiu a0`) comes before `mtc1 f12`:** a
  `static inline` wrapper taking only `void *p` that does the cast and passes the constants. (b244:01E02B40)
- **A call to a static sibling defined earlier passes one more argument than its definition, or its argument
  registers are set in another order:** declare the sibling by its real name as a block-scope extern with no
  prototype (`extern void func_01E00920_b098();`) and pass what the asm shows. (b098:01E01F30, b494:01E013C0)
- **A sign-extended value meant for a saved register lands in a temp before a `div`:** assign it to its s16 local
  first and divide in place, `step = s->col.a; step /= (s16)(n * 3);`. (b092:01E04290)
- **A call matches in `dk try` but `tools/mod_infile.sh` says "undefined identifier":** the callee is a static
  defined later in the file (`#include "mod/<mod>.c"` hides this); call it by its link name `<mod>_<VADDR>` through a
  block-scope extern with no prototype. (b494:01E013C0)
- **`work/port.py` drops a donor's `#pragma opt_propagation off` / `reset` pair:** `dk try` matches but the module comes out
  bigger and later `jal` targets shift, since the pragma stays on for every later function. Copy both lines.
  (b498:01E03710)
- **`dk try` stuck at N-2/N, the only difference `%%hi/%%lo(D_X+4 label)` against `%%hi/%%lo(D_X)` on a field read of an
  indexed module table:** the words are the same; splat just put an extra label inside the table. Do not declare
  the label; check with `work/fulltry.sh`, then splice by hand (`work/splice.py`) and run the full check, since
  `dk accept` refuses on the name difference. (b712:01E00FD0)
- **The original keeps `i` and computes `addu v0, i, i; addiu v0, 1; sll`, yours counts a register up by 2:** write the
  index as `out[i + i + 1]`, not `out[i * 2 + 1]`. (b773:01E017B0)
- **A value read twice is loaded into a saved register in a `jal`'s delay slot and reused after the call
  (`rand() % (2t) - t`):** write the field read straight into the expression, `func_0019A5C8() % (g->t * 2) - g->t`;
  a named local or an inline helper moves the loop counters to other saved registers. (c603:01E00E10)
- **`dk perm` says "no better version found" at once:** `base.c` has the `__builtin_offsetof` layout checks; delete
  them from `nonmatchings/<func>/base.c` and run `permuter.py` yourself. (c603:01E00E10)
- **A stack vector's address taken once before a loop (`addiu sN, sp, &p`), `.x` read through `sN`, `.y` straight from
  `sp`:** make it the second element of an array with the stack vector below it, `Vec4f t[2]`, and use `t[1]`.
  (b740:01E01F30, as b353:01E02660)
- **Two argument addresses computed in the other order at a join:** a cast on the struct-address argument, even to
  its own type (`(Emit_b000_01E01140 *)&g->emit`), restores the order. (b740:01E01F30)
- **An extra `andi v0, 0xFF` before a u8-to-float conversion:** drop the `(u32)` and write `(f32)o->c86`; a u8 already
  converts as unsigned. (c021:01E00E00; the reverse of c021:01E03390)
- **A run of `if (g->n == k)` blocks, each with a short copy loop; only the first loop matches, or the base folds into
  the store offsets:** give each block its own `{ s32 i; Vec4f *p = g->row[k]; for (...; i++, p++) ... }`. (b136:01E002E0)
- **A float tested against zero with the zero and the value in each other's registers (`x != 0.0f` and `0.0f != x`
  alike):** write the bare test, `if (v.x)`. (b191:01E01A70)
- **A value read just before a call to a static sibling lands in `$a0` where the original has `$a1`:** drop the cast
  on the struct-address argument (the reverse of the b740 tip). (b292:01E02580)
- **`dk try` alone is one off (an argument address before a float `mtc1`) but `tools/mod_infile.sh` matches:** trust the
  in-file result and leave the call alone (the float-local and inline-wrapper fixes broke it in the file); splice
  by hand and run the full check, since `dk accept` refuses. (b489:01E00FA0)
- **-O1 scene manager with the scene pointer in the lowest saved register where the original has it in the highest:**
  take the scene as a typed parameter (`Scene *g`), not `s32 arg0` plus `g = (Scene *)arg0;`. (b181:01E03830)
- **`lw`/`sw` where yours has `lwc1`/`swc1` copying one field into a vector local:** type the field and the local as
  s32 (a struct of four s32), not a pointer cast at the store. (b773:01E038D0)
- **A loop counter spilled to the stack and the frame 0x10 too big, with two neighbouring stack vectors each held by
  address in a saved register:** declare them (and the vector before them) as one `Vec4f v[3]`. (b042:01E05C20)
- **No twin by name, `shapes.py similar` and `port.py scan` find nothing:** rank the C functions by how close their
  sequence of main-program calls is to the target's (`difflib` over `port.calls()`, `work/gus3/callsim.py`); the top
  hits give donors for parts of the body. (b598:01E055C0)
- **In a call to a static sibling, a later argument's address (`addiu a3`) set before `li a2`:** cast the first two
  arguments `(void *)` and pass the late one bare; a cast on it brings the early `addiu` back. (b546:01E021E0; see the
  b740 and b292 cast tips)
- **Two calls passing the same two zero float arguments, the copy between `$f14` and `$f15` going the other way in
  the second:** declare two float locals last, set them to 0.0f before the first call, pass literals to the first
  call and the locals to the second. (c613:01E02540)
- **A pointer-walk copy loop with no call inside, the counter and pointer in each other's temps (`$v1`/`$a0`):**
  give the loop its own block counter declared before the pointer, `{ s16 k; Vec4f *p; ... }`. (b702:01E013E0;
  see b136:01E002E0)
- **A run of `x == 104 || x == 105 || ...` kept as one `beq` per value where yours becomes a range check (`addiu; sltiu`):**
  the function is -O3. (b053:01E010F0)
- **Scene manager with two counted draw loops, the second's counter and count in each other's saved registers:** run
  the second loop on the first loop's count variable and count in its counter, `j = 0; for (n = 0; ...) if (used) j++;`.
  (b053:01E010F0)
- **Two calls each loading two float constants, the block-local `f32 r = K;` fix for the second flips the first (in the
  file):** add a `(void *)` cast on the first call's pointer argument, or pass both its constants as locals. Small
  unrelated changes (a parameter's u32/s32, `!= 0` or a bare test) can flip these orders too; judge in-file. Retried
  hard rows b591:01E048E0 and b648:01E04F40 matched this way.
- **Two constants in one expression (`15.0f + 5.0f * k`) loaded in the other order, no float-local or wrapper form
  helps:** check a same-shape twin for `#pragma opt_propagation off`. (b065:01E01BA0, from b235:01E02370)
- **A float constant passed to an earlier call in the same block, and the next call's constants load out of order:**
  put it in one function-scope local and pass that local to both calls. (b037:01E05F30)
- **`f(p, A, B, A)` with the original loading B first and copying A from `$f14` to `$f12`:** pass the middle constant
  through a block local, `{ f32 r = B; f(p, A, r, A); }`. (b774:01E02F60, c059:01E031C0, c027:01E01930)
- **Two calls `f(x, 1.5f, k, 1.5f)` in a row, the second copying `$f14` to `$f12`:** pass the second call's array as
  `&sc[0]`, not `sc`. (c021:01E02350)
- **`work/fulltry.sh` now prints FAILED on a splice or build error.** Before 2026-10-29 it could print a stale OK.
- **Three calls `f(&sc[k], 1.0f, 0.2f)` in a row, only the last loading 0.2f first:** declare `f32 one;` at function
  scope, set it just before the first call, pass it only in the last. (c532:01E01040)
- **The divisor and the step's `cvt.s.w` hoisted above the table loads in the original:** fold the multiply into each
  delta, `dx = (a.x - b.x) / 50.0f * o->step;`, with no step local. (b709:01E055C0)
- **Scene manager draw loop, the function pointer and the slot pointer (or counter) in each other's saved registers:**
  keep `draw = g->slot[i].draw;` but test the field again, `if (g->slot[i].draw != NULL)`; if the same variable serves
  the handler loop, give that loop its own `fn` local. (c034:01E00350, c006:01E00B80)
- **The c532 `one` trick goes on whichever call loads its second constant first in the original** (the second of
  three in c531:01E01040).
- **One counter for two loops, one with a call and one without, the later loop's counter swapped with a saved local:**
  give the loop without a call its own counter. (c059:01E00340)
- **A parameter copy (`paddub sN, aX`) scheduled after the field load that uses it, where the original has it before:**
  declare the callee's matching argument with its real narrow type (`s16`) in the block-scope prototype. (b192:01E03920)
- **A loop-invariant mode in a saved register, swapped with the loop's pointer register:** drop the mode local and test
  `(flags & 0xF)` in each `if`. (b582:01E04B10)
- **An all-zero float call `f(g->v, 0.0f, 0.0f, 0.0f)` with its `mov.s` order wrong in the file:** a `(void *)` cast on
  the pointer argument. (c017:01E009E0)
- **An array address `addu v0,v0(idx<<4),sN` where yours has `addu v0,sN,v0`, read through a cast parameter:** use a
  typed local copy of the parameter, declared last, and read through it. (b120:01E044A0)
- **A stack zero stored through an address temp (`addiu v0,sp,X; sw zero,0(v0)`) where yours stores directly:** copy the
  field from its neighbour, `q[1].y = q[0].y;`; it can also move nops near calls, so judge in-file. (b774:01E04530,
  b115:01E02A10)
- **Before retrying a hard row, grep its real name:** its shape may already be C under a sibling id (c604:01E03200 was
  c611:01E00A80's source as is).
- **A field store scheduled after unrelated stores although its value loads before them, the local's address taken:**
  copy it to a spare local before those stores and store the copy after them. (c544:01E01F60)
- **Frame 0x10 short with 8-byte gaps around a packet:** out buffers `s32 [2]` / `s32 [3]` and an 8-byte packet tail;
  a draw context swapped with a CSE pointer goes back in the parameter (`ctx = ...`). (b151:01E027D0)
- **Frame 0x20 short in a 4-vertex textured packet (out buffer `u8 [4]` at the frame top):** give the packet a
  `u8 tail[0x20]`, as b029:01E04780's packet has. (b029:01E05AA0)
- **A by-value vector argument to a static sibling with `addiu a3, sp, &v` set too early:** declare the local with the
  callee's own parameter type, not `Vec4f` cast at the call; cast the other way only where the other type is taken.
  (b219:01E02920)
- **Only spill slots differ, the loop bound and another spilled local in each other's slots:** drop the `last` local and
  test `i < n - 1` in the condition; even an unused `last = n - 1;` changes it. (b589:01E03470)
- **Quick scorers for scheduling/declaration searches:** `work/kr2perm.py` (every order of named declarations, 720 in 20
  s), `work/kr2move.py` (one statement to every position), `work/kr2var.py` (a list of replacements); set `KR2F=<func>`.
- **One spill slot 4 off after the declaration order is right:** `__attribute__((aligned(8)))` on that s32 local.
  (b415:01E03930)
- **PAINT_RAIN20/21 grid draws (b215, b152, b597) with row pointers spilled:** b232:01E01B90's form with plain 2-D
  indexing; the band drawers b509/b161 are not donors. (b215:01E04010, b215:01E03AC0)
- **An s16 angle temp in a saved register swapped with the loop count, no declaration order helps:** set it in two steps,
  `a = o->ang0; a = a - 8;` (permuter). (c022:01E010E0)
- **The b244 constant-order effect can land on the new function itself:** its right form depends on whether another
  new function earlier in the file is in; check both together (`work/bothtry_c059.sh` is an example). (c059:01E03D70)
- **A field value loaded before a struct-copy table load and stored after it:** read it into a pointer local declared
  last, before the copy. (c611:01E01050)
- **Link-name externs for later siblings can crash mwcc in the full build:** forward `static` declarations build and
  match there. (b117:01E00CB0)
- **At -O3, a `&v.y` address set inside the loop where the original hoists it differently:** `#pragma
  opt_loop_invariants off`. (b117:01E00CB0)
- **A GenAuraTex row stuck on frame size or packet offsets:** port b711:01E054B0 with `work/port.py` and fix the colour
  bytes by hand. (b768:01E01D90, b216:01E052E0)
- **A stack-array element address (`&v[3].x`) kept in a saved register across a call, yours rematerialised:** drop the
  `(u32)` casts and pointer locals and write plain `v[3].x`. (b443:01E01B00)
- **A loop value and a strength-reduced pointer in each other's saved registers:** keep the value in an earlier local
  that is dead by then (`r = g->ids[i];`). (c062:01E039E0)
- **Extra nops at the ends of if-blocks and loops, delay slots copied from the target but the branch not moved:**
  `#pragma conditional_move off`. (b716:01E060B0)
- **Early exit as `beqz $at, skip; nop; b end` where yours has one `bnez`:** one combined `if (x < lo || x > hi) return;`.
  (b716:01E060B0)
- **Float `c += k * (t - c)` steps subtracting in the wrong order:** fold k into each delta (`d = k * (t - c); c += d;`);
  if one pair still swaps, keep its deltas in later temps that a later block reuses. (c536:01E00120)
- **Scene manager with the sine-table loop's counter and pointer swapped:** give the texture loop its own counter declared
  last and run the sine-table loop on `i`; count draws with `n++` before the kind check. (c022:01E00C70, c051:01E00590)
- **A whole saved-register map shifted by a strength-reduced pointer:** route the element through an earlier pointer local
  reused later in the loop (`j = (s8 *)&o->ids[i]; ... j = tbl + i;`); a fresh pointer local does not help.
  (b357:01E02180)
- **Stack temps each followed by an 8-step `lw/lw` copy loop into a matrix array, after calls with `a0` = the temp:** the
  callee returns a struct; declare `typedef struct { f32 m[16]; } Mat;` and write `m[k] = func_00108EF0(...);`. (b056:01E03B40)
- **A second `if (p)` with a redundant `beqz` on the same register at the tail of the first branch:** put the test
  inside the first branch, not after the if/else. (b056:01E03B40)
- **Screen UVs: `div.s` writes into the int's `cvt` register and the divisor and second value swap FPRs:** set both values
  first, then divide each in place (`u = ix; v = iy; u /= -16.0f; v /= -16.0f;`). (b413:01E037E0)
- **An integer address chain folded into one register in yours:** read the packet through `g->pk->...` at every use, not a
  `pk` local. (b413:01E037E0)
- **`work/kr2perm.py`/`kr2c.sh` scores mean nothing for a draft with `#include "mod/<mod>.c"`:** they compare the whole
  module object; drop the include (or use `tools/mod_infile.sh`) when scoring.
- **A float step with its `add.s` operands swapped, or stored and reloaded:** write `x += K;`, not `x = x + K;`.
  (b218:01E02160, b353:01E01010)
- **Several copy loops with one body under different `if`s, only the first matching:** give each loop its own counter
  (`i`, `j`, `k`, `l`). (b353:01E01010)
- **A ±1 sign set with `li; li; movn` where yours branches:** `if (i == 0) s = 1; else s = -1;`; the `?:` forms branch.
  A zero-init in the wrong place before a loop: put it in the for-init (`for (j = 0, a = 0; ...)`). (c059:01E06720)
- **Running sums updated by float-to-int calls at the end of a loop, spill slots not following declaration order:**
  the source is `((s32)f * i) << 4`; the compiler makes the sums itself. (b015:01E008F0)
- **A new function matches in-file but flips a later function's float constant loads in the full build:** first try the
  header prototypes instead of the new function's block-scope externs. (b037:01E03E90 vs b037:01E05F30)
- **Hoisted pointers to the second u16 of a stack struct (`addiu sN, v0, 2` kept across a loop):** write both fields through
  `((T *)(s32)&local.sub)->field`. (b037:01E03E90)
- **Index register swapped with a stored constant in `g->slot[g->next]` stores:** `g->slot[i = g->next].used = 1;`.
  (c403:01E00080)
- **Two (0.0f, 0.0f) calls with the `mtc1 $zero` register differing, one shared pair of locals fixing one and flipping
  the other:** set them again right before each call (`h = y = 0.0f;`) and pick the argument order per call; the
  last-assigned local gets the `mtc1`. (c518:01E031E0)
- **`lh; addiu v1, v1, -1; sh` where the original writes a new register:** `x - 1U`. (c518:01E031E0)
- **Two stack colour arrays passed side by side, the second's address taken first:** one `u8 col[8]`, passed as
  `col, &col[4]`. (b047:01E01990)
- **A stack out-buffer address kept in a saved register across a loop, with a gap below it:** make it a later member of a
  stack struct, passed as `out.o`. (b180:01E025C0)
- **Per-quad tables in a nested grid loop walked by spilled pointers that step through both loops:** index them by the
  s16 draw counter running across both loops (`g->h[cnt]`). (b430:01E03DB0)
- **A lone `slti $at, $v0, K` nothing reads, right before another compare of the same value:** an `if (x > K-1)` whose
  body the optimizer drops late (`if (g->frame > 150) m = 0;` with m already 0); empty bodies are dropped too early.
  (b520:01E01730)
- **An -O2 scene manager with `g` and `code` in each other's saved registers:** `(Scene *g, s32 arg1)` with
  `s32 code = arg1;` as the first local. (b075:01E05230)
- **`b[i] = a[i] = -1;` putting the `sll` before the `li -1`:** two separate stores. (b075:01E05230)
- **A second pointer in a scene manager's draw loop stepping by 0x40 beside the slot pointer's 0x70:** a separate table
  parallel to the slots, just before them; index it with the slot counter. (b495:01E02D80)
- **A local converted from a float result lands in the next free saved register, the original has it highest (just
  below the scene pointer):** check the caller; an extra argument it passes (`a1 = 0`) is a parameter reused as that
  local. (b120:01E00B70)
- **`addiu a3` before `li a2` for a slot-position argument passed by value as the callee's own vector type:** make the
  slot field a union of `Vec4f` and that type and pass the member, not `*(T *)&slot.pos`. (b065:01E02DB0)
- **`lw/and/or/sw` on a stack colour word where yours gets `sb`:** explicit masks on a u32 (`w = (w & 0xFFFF00FF) | (g << 8)`).
  (c560:01E01E40)
- **Packet bitfield writes through address registers where yours folds into sp offsets:** declare the field u64 and
  write through a cast, `((Uv *)&p->v[i].uv)->u = ...`. (c560:01E01E40)
- **An s16 loop counter tested with `if (i == 0)` inside the loop, yours testing an extra sign-extended copy:** write
  `if (!i)`. (b594:01E01840)
- **Scene manager frame 0x10 too small, the original copying a slot position to a stack temp before a by-value call:**
  declare `Vec4f pos;` before the rm buffers and pass `pos = g->fx[k].pos; f(..., pos);`. (b362:01E02BA0)
- **A 16-byte struct-return slot before an earlier-declared local, its copies after it:** have both calls return into one
  aligned-16 local (`c = f(...); q[0] = c.v; q[1] = c.v;`). (c062:01E00730)
- **The 8-byte return slots of four `func_00107740` calls in descending order, yours ascending:** a `static inline` helper
  for the four uv sets. (c062:01E00730)
- **A local's spill slot after the compiler temps, right before the spilled parameter, no declaration order helping:** it
  may be an extra parameter reused as that local (`..., s32 n) { n = o->n;`), even if callers pass fewer arguments.
  (b025:01E03E90; its LkSort sibling takes four parameters)
- **`dk perm` scores 0 at once when only spill slots differ:** it ignores stack offsets; score with `work/kr2c.sh`-style
  scripts instead. (b025:01E03E90)
- **Spreading by hand:** keep the donor's shape comment and type suffixes and change only the name, include and helper;
  `house.py` would turn the copy into a shape of its own. (b025:01E03E90's 8 copies)
- **14-bit texture coordinates from `(s16)(base + i * q) << 4` sign-extended or shifted in another place than yours:** put
  the sum in a local first, `t = (s16)(...);`, then `t *= 16;` on its own line, placed just before the first store.
  (b047:01E01270)
- **A draw at `pos + vel * h` with the int-to-float conversion of h out of place:** convert it once into an f32 local
  before the first store and multiply by the local. (b434:01E02570)
- **An `if` whose bit test sits at the bottom of its block, entered by a `b`:** `while (cond) { ...; break; }`. (b023:01E00990)
- **A cue-table loop masking both `t` and `e->start` with `andi 0xFFFF`:** `t >= (u16)e->start`. (b023:01E00990)
- **Store order of `a = b = c = d = K`:** d first, then a, b, c. (b023:01E00990)
- **A lone `addu vN, vN, $zero` after a `% K` (the block of several `rand() % K + c` where c is 0):** add a local holding
  zero (`s32 base = 0; ... % 144 + base;`); a literal `+ 0` is folded away. (b731:01E01F40, b550:01E02130)
- **An extra saved register holding `g + k*size` across calls where the original keeps only the offset:** copy into the
  slot through a pointer local (`r = g->rib; *(Vec4f *)r[k].pos = v;`), not straight into `g->rib[k]`. (b024:01E04CC0)
- **`dk perm` gives up at once on a draft with `#include "mod/<mod>.c"`:** `base.c` carries the layout checks; run
  `sed -i "/__builtin_offsetof/d" nonmatchings/<func>/base.c` and `permuter.py` yourself. (b024:01E04CC0, as c603)
- **A big manager where each fix to one argument-order or `mtc1` difference flips another call:** change how a member is
  spelled or typed, not only the cast (`g->mdl.r` for `&g->mdl`, `g->line + 1` for `&g->line[1]`, `s32 v[4]` for a
  `Vec4f` read as ints); script the combinations. (c560:01E02720)
- **Point sums `p.x = it->x + out[j].x * it->scale` with the scale loaded before the component:** read the vectors through
  a walking pointer (`for (j = 0, q = out; ...; j++, q++)`), not `out[j]`. (b105:01E02190)
- **`x / n` and `x % n` in one branch as `div` + `div1` in parallel, yours dividing twice with a reload:** write the
  `%` statement before the `/` one. (b105:01E02190)
- **A real `mul.s` by a zero that was just stored:** a float local set to 0.0f, used for both the store and the multiply;
  a literal `0.0f * x` is folded away. (b139:01E01910)
- **The b244 `static inline` wrapper taking `void *p` still leaves `addiu a0` after `mtc1 f12`, and the struct
  behind the address was just filled from a shared constant register:** type the wrapper parameters as the real
  struct pointers and keep the cast (`(s32)p`) inside the wrapper. (c533:01E031E0)
- **Four stores of one value into four packet vertices come out v3, v2, v1, v0:** write one chained assignment
  `v[0].r = v[1].r = v[2].r = v[3].r = c;`. The order of the middle stores does not follow a simple rule
  (`v[2]=v[1]=v[0]=v[3]` gives v3, v2, v0, v1), so script the six orders of the first three targets. A two-target
  chain stores the rightmost first. (b223:01E03160)
- **A call with four float constants loads `$f15` before `$f14`, and the next call puts its argument address
  before its `mtc1`:** pass only the last constant through a block local, `{ f32 h = 6.0f; f(p, id, A, B, C, h); }`.
  That one change fixed both calls. (c529:01E01B90)
- **`(f32)(a - b) * (x * s)`: the original does `x * s` first and converts the int afterwards, ours does the
  `mtc1`/`cvt` first:** put the difference in a block-local s32, `{ s32 d = a - b; dx = d * (x * s); ... }`, and
  multiply by `d` with no cast. (b083:01E04D80)
- **A constant stored once (`li a2, 1; sh a2, ...`) gets a register one above ours, and an `s32` local for it
  still lands one low:** the original has `$a1` blocked there; use a spare parameter as the local,
  `(s32 arg0, s32 id, s32 o) { ... o = 1; g->rm[1] = o; }` (like b120:01E00B70 and b025:01E03E90). (b082:01E02860)
- **A step loop that skips some handlers and counts them: the original falls through to the `jalr` and branches to
  a shared `m++`, ours puts `m++` right after the `bne`:** write `if (fn != A && fn != B) fn(g, slot); else m++;`,
  not `if (fn == A || fn == B) m++; else fn(g, slot);`. (b092:01E03950)
- **A block-local `f32 v = K;` fixes one call's address/`mtc1` order but flips it in a later call:** declare the
  float local at function scope and assign it just before the call (`f32 v; ... v = 20.0f; f(&g->rain, 64, v);`).
  (c557:01E01AC0)
- **An -O2 draw has a `beqz` to a lone `nop` block, and the `then` arm ends in a `b` past it, right after a flag test
  that sets a float to 0.0f:** the source has an `else` copying a value already in that register,
  `if (f & 0x80) { xy.z = 0xFFFFFE; z = 0.0f; } else { z = d; }`. The copy folds away but the empty arm stays.
  (b133:01E00410)
- **A spill slot 8 bytes too low that no declaration order moves:** `__attribute__((aligned(16)))` on that s32
  local (`aligned(8)` was not enough). (b133:01E00410)
- **At -O2 a chained assignment `a = b = c = d = K;` stores straight right to left (d, c, b, a):** list the targets
  in the reverse of the store order you need; `c44[2] = c44[1] = c44[0] = c44[3] = 0xC0;` stores 3, 0, 1, 2.
  (b368:01E05440)
- **A stack address read with direct `sp` offsets in one part of the function but held in a saved register across a
  loop in another:** the address of a plain variable is never kept in a register, but the address of an array
  element at a non-zero offset is, from its second use on. (b741:01E02E50)
- **A pointer local whose saved register comes too low:** also assign it in the other branch where the same address
  is used (`func_00103290(c = (Vec4f *)&tex[0], 0)`). Once it is assigned in both branches, its declaration order no
  longer matters. (b741:01E02E50)
- **In a chain of `if/else if` tests on a value computed just before it, only the first test should come out as
  `slt v0; xori v0, 1; beqz` (or `slt v0` where ours has `slt at`):** assign the value inside that first test,
  `if ((t = expr) <= K)`. If a second chain's temps still land in permuted registers, give that chain its own
  block-local variable and swap the operands of its first test (`if (K > (d = expr))`). (c508:01E015C0)
- **A manager's frame is 0x60 too small and a saved register holds a high stack address (`sp+0xD8`) passed as one
  call's out argument:** the argument is a field inside a stack packet the function never uses otherwise; declare
  `u8 pk[0x90];` last and pass `&pk[0x18]`. (b577:01E01EE0)
- **An extra `jal fptodp` before a call to a static of the same module that takes an f32:** a no-prototype
  block-scope extern promotes the float to double; call the static directly (with casts on the other arguments) so
  its real prototype applies. (b084:01E02E50)
- **An if/else whose then-arm has a store in its `b` delay slot equal to the else-arm's last store (after a `nop`
  following its `jal`), with one more `nop` at the join; ours has the store written in each arm and two nops
  missing:** write the shared statement once, after the if/else. The delay slot copies it from the join.
  (b572:01E024D0)
- **A loop with an index that also steps other values by fixed amounts: the original gives the index the last saved
  register (after the compiler's array pointer), ours gives it the first whatever the declaration order:** write
  the stepped values as expressions of the index (`i * 20`, `i * 20 + 20`, `i * 10 - 45`) rather than separate
  variables added each pass. The compiler makes its own running values and the index is left for the loop test.
  If an earlier simple loop then takes the wrong registers, give it its own counter, declared first.
  (b266:01E01D50)
