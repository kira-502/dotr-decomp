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
  to each copy. (Fixed 26 Oct: the tool now carries the pragma lines, their resets and the comments above the
  function.)
- **Accepts carry your own name:** `dk accept` commits with your `git config user.name` / `user.email` (set both in
  the repository; it stops if either is missing).
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
- **In a scene manager only the step loop has its counter and slot pointer in each other's saved registers, and the
  setup's random-table loop counts with the draw counter `m`:** count that setup loop with `i` like every other
  loop. Using `m` there is what swaps the step loop. (b513:01E02690)
- **A static sibling's pointer argument `&slot.pos` comes out as `addiu a3` before `li a2`, and no cast form moves
  it:** make the slot field a union of `Vec4f` and the callee's parameter type and pass that member with no cast
  (the b065 union fix, for a pointer argument). (b492:01E038C0)
- **In `func_00205440(pt, m, &pkt.v[k].xyz, &d[k])` calls, `addiu a3` (the `&d` argument) comes before `addiu a2`,
  and no cast fixes it:** declare it by block-scope extern as b049:01E02690 does,
  `extern s32 func_00205440(void *, void *, void *, f32 *);`, and pass the addresses with no casts.
  (b025:01E00910)
- **A float temp and the constant it is multiplied by (`3.1415927f * e->ang / 180.0f`) sit in each other's FPRs
  (`$f1`/`$f2`) and no operand order changes it:** do the degree-to-radian step through a
  `static inline f32 rad(f32 d) { return 3.1415927f * d / 180.0f; }` helper. (b457:01E04300)
- **An element address built as `addu v0, v0(idx<<1), sN(base)` where ours has `addu v0, sN, v0`, and every
  `&e->h[j]` / `e->h + j` / `(u8 *)` spelling and a typed local copy leave it reversed:** write it as an integer
  sum with the shifted index first, `(s16 *)((j << 1) + (s32)e + 0x2C)`. (b268:01E03FE0)
- **A two-case `switch` that returns constants tests its values in the reverse of ours:** list the cases in the
  other order (MWCC emits the tests in reverse source order here); an if chain branches differently.
  (b596:01E03DA0)
- **A static call's struct-address argument (`addiu a0`) comes before its float constant's `mtc1 $f12`, and the
  b244 `void *` inline wrapper makes that call worse:** put an `(s32)` step inside the cast,
  `f((T *)(s32)&g->member, n, K)` (`(void *)(s32)` works too). (b049:01E032E0)
- **In a loop, a short-lived pool-record address and the loop's strength-reduced pointer sit in each other's
  registers (`$v1`/`$a1`), and no spelling of that statement changes it:** write the record through the same
  pointer variable in an earlier loop as well (`(r = &pool[id])->life = 0;`), and use one counter name for every
  loop of the function. Neither change works alone. (b444:01E03C10)
- **Module switch functions:** since 9b663245 `tools/jtbl_fix.py` takes module table names (`jtbl_<VADDR>_<mod>`),
  so a plain C `switch` compiles and points at the module's own table; before that every module switch stopped with
  "its asm uses 0". (b172:01E02F30)
- **Four vertex q values, s/t reuse q from registers, the 1/d divides in an odd order:** write `v[0].q` straight
  from its divide, then `q1`..`q3` into locals right after; of the 24 orders only that one matches. (b172:01E02F30)
- **Around a `jal func_001A23B0`/`func_001A22C0` every temp sits one or two registers higher than yours
  (`$a2`/`$a3`/`$t0` for your `$a0`/`$a1`/`$a2`), `$a0`/`$a1` unused:** those are the compiler's `fptoui`/`fptosi`;
  write `(u32)x`/`(s32)x` instead of calling them (the cast keeps `$a0`/`$a1` blocked up to the call).
  (b132:01E04B00, b398:01E05600)
- **Sums like `27648.0f - fx` sit inside each switch case in the original, yours are hoisted before the loop:**
  compute `fx` inside the inner loop (after its `continue`); at -O4 the compiler still hoists `fx` itself but leaves
  the expressions built from it in place. (b172:01E012E0)
- **Two float variables of an -O4 function in each other's registers, no declaration order fixes it:** look for an
  -O1 build of the same source in another module; at -O1 registers and spill slots follow the declaration order
  directly, so its matching declaration list shows the real order, and that list matches the -O4 build too.
  (b285:01E03B50, b177:01E02FC0)
- **An outer and an inner loop counter in each other's saved registers, no declaration order swaps them:** swap the
  counter names between the loops (`j` outside, `i` inside). (b070:01E046A0)
- **`k == 0 || k == 1` folded into one `sltiu` where the original has two compares, and the function is not -O3:**
  write it as a `switch (k) { case 0: case 1: ... default: ... }`. (b210:01E04B10)
- **Every saved register one off (the `func_00207500` result in `$s0` where the original has `$s7`), no declaration
  order moves it:** look for one counter name reused by two unrelated loops and give one of them its own variable.
  (b512:01E00080)
- **A module whose jump tables sit in the literal pool (`.word .L<VRAM>_<mod>` in `asm/data/mod/<mod>_pool.rodata.s`;
  b512, b541, b543):** since b7dec2ad the linker script answers those labels with their addresses, so the module
  links once the function is C; regenerate the scripts with `python3 tools/modules.py ld <mod>` if yours are older.
- **Floats set from one another (`ra = e->r; rb = ra * e->k;`) and their hoisted squares in permuted registers, no
  declaration order fixes it:** read the field again instead of the variable, `rb = e->r * e->k;`. (b051:01E00DF0)
- **A shifted difference used twice (`d = (w1 - w0) >> 1; w0 += d - 1; w1 -= d - 1;`) with it and the address temps
  around it in permuted registers:** keep the unshifted difference in the local and shift at each use,
  `k = w1 - w0; w0 = w0 + (k >> 1) - 1; ...`. (b062:01E00DF0)
- **Before a call to a module static, the address argument (`addiu a3`) loads one instruction ahead of a constant
  (`li a2`), and no statement order fixes it:** call it through a block-scope no-prototype `extern void f();` with no
  casts on the arguments. (b256:01E04090, b264:01E03E00)
- **`func_001031C0(g->wv, g->t)`: your `lhu $a1` (the counter) comes before the original's `addiu $a0`:** declare it
  `extern void func_001031C0(void *, u16);`. (b190:01E037A0, b126:01E04FE0)
- **An -O1 struct copy into an array element gives `addu $v1, $s3, $v0` where the original has `$v0, $s3`:** do not
  cast an `f32 pos[3]` member to `Vec4f *`; give the element a local type with a real `Vec4f pos` and cast the pool
  where it is passed on. (b126:01E04FE0)
- **Packet tail copies through `addiu aN, sp, X; ld/sd 0(aN)` where yours stores to sp offsets directly:** make the
  field an 8-byte struct (`struct { u64 d; }`) and copy it as a struct. (b739:01E03220)
- **`x * 1.0f` kept as a real `mul.s`:** `w = 1.0f; r = s * w;` with `r` an already declared float. (b739:01E03220)
- **A spread copy makes the module's scene manager (already C, further down) swap a float `mtc1` and an address
  `addiu` before a call:** the b244 effect; assign the constant to an existing float local, `r = 3.0f` in the
  argument list or `r = 3.0f;` just before the call (which one varies by module), and commit it with the copy. A
  per-copy whole-module compile finds such copies before `dk accept` rejects them. (b489:01E00240 with b489, b581,
  b391)
- **An -O1 port of an -O2/-O3 twin has a frame 0x10 too big with an extra `swc1 $f28`:** the twin's float temporaries;
  write each sum out in full at every use (-O1 recomputes it anyway). (b241:01E00440)
- **An -O2 port where every saved register is shuffled and the first parameter lands in `$s6` instead of `$s0`:**
  `#pragma opt_propagation off`. If an if/else's then-arm then branches straight to the following loop's test where
  the original goes through the join, compute the start into its own variable, `for (j = st; ...)`. (b110:01E01B20)
- **The module spline inlined (mula.s/madd.s weights, no `jal`):** b081:01E009A0's body as a `static inline` helper;
  weight registers in the wrong order: declare the weights in reverse (`f32 b3; f32 b2; f32 b1; f32 b0;`).
  (b847:01E00E60)
- **An -O3 port misses a block-end `nop` or two (end of an else arm, end of a later `if (k == 0)` block):** turn the
  `?:` into an if/else assigning the undivided value and write the divide at each use,
  `(u32)(a / (f32)segs * (f32)(segs - k))`; the compiler hoists the shared divide itself. (b285:01E003A0)
- **A clamp's branch keeps a `nop` delay slot where your `if` fills it:** write it as `?:` (`n = n > 36 ? 36 : n;`).
  If that swaps the variable's spill slot with another spilled local, reuse the other local for an earlier
  short-lived value so it becomes a split web with a later slot. (b062:01E020A0)
- **`f(p, A, B, A)` where the original loads A into `$f14` and copies it with `mov.s $f12, $f14`:** assign a block
  local inside the last argument, `{ f32 r; f(p, A, B, r = A); }`; `f32 r = A;` before the call gives `$f12`.
  (b136:01E020D0)
- **Two neighbouring stack vectors, the original reads `b.x` through the address register it built for a call
  (`addiu s0, sp, &b`) and keeps `&a.y`/`&a.z` in saved registers:** declare them as one `f32 v[2][4]` and write
  `v[0][k]`/`v[1][k]`; no pointer local or cast does it. Two colour buffers side by side: one `u8 c[8]` passed as
  `c, &c[4]`. (b183:01E01480, b491:01E02370, b197:01E01A10)
- **An s16 field tested `x == 0 || x == 1`, the original `beqz` on the loaded value, then re-extends it
  (`dsll32`/`dsra32`) before the compare with 1:** write `if (!g->mode || g->mode == 1)`. (c062:01E03BE0)
- **An s16 counter tested after its loop comes out `dsll32`/`dsra32` + `beqz` where the original has a bare `beqz`:**
  write `if (j)`, not `if (j != 0)`. (b734:01E033C0)
- **`dk try` differs only in a relocation name inside a module table (`D_..B4` where yours is `D_..B0[k].field`):**
  the bytes are the same; check with `work/fulltry.sh` / `dk accept`. (b133:01E00BA0)
- **Per call site, a module static can go through its no-prototype alias (`extern void <mod>_<VADDR>();`) or its
  real prototype:** when one call's struct-address argument or delay-slot store is out of order, switch only that
  call to the alias. A struct return copied out through `paddub $v0, $a0` needs the real static. (b178:01E042E0,
  b152:01E03730)
- **`f(p, A, 0.0f)` loads `mtc1 $zero, $f13` before `$f12`:** both constants in block locals,
  `{ f32 x = A; f32 h = 0.0f; f(p, x, h); }` (one alone is worse). (c610:01E01180)
- **Scene-manager step loop with its s16 counter and slot pointer swapped (the pointer should get the lower register)
  while the draw loop matches:** a counter used in only one loop gets its register before the strength-reduced
  pointer; one also used by the setup loops gets it after. Run the setup, step and draw loops on one s16 counter. If the
  slot count then swaps with that counter, zero the counter at the top before the count (`k = 0; m = 0;`): among
  multi-loop variables the one mentioned first gets the lower register. Declaration order did nothing there
  (it did matter in b060:01E013C0, whose step counter had to be declared first) (b594:01E02EC0, b494:01E013C0, b281:01E02440). When the count is itself a setup counter, put the step and draw loops
  on the setup's other counter and zero that first (`a = 0; m = 0; k = 0;`) (b215:01E02E50). Repro in work/wall2/.
  The reverse case: the slot count in the lowest saved register with the step/draw counter higher means the setup
  loops run on the step/draw counter and `n` is only `n = 0; ... n++` (b073:01E02D30, 649 → 708).
- **An -O4 range test gives `slti $v0` + `bnez $v0` where the original has `slti $at`, and `> K-1` alone does not
  fix it:** nest the two bounds, `if (x > K-1) { if (x < L) ... }`, instead of `&&`. (b378:01E00970)
- **A range test's first compare at -O3 gives `slti $v1, t, K` + `bnez` where yours has `slti $at`:** write the low
  bound `t >= K` (the reverse of the `> K-1` tip); keep `>` where the original uses `$at` for both. (b363:01E02070)
- **A module global sits at an address splat labelled as a function (a `piece` after the code, or a stale epilogue
  slot):** declare it under that label, `extern T *func_01E02900_b296;`; no `D_` label exists there.
  (b296:01E01FD0, b723:01E053E0)

- **Porting a scene manager with work/port.py.** `port.py try` reports -1/0 at every level when the donor calls its own
  module's statics by name (`func_01E02170_b516`): they don't exist in the target, so nothing compiles. Rename those
  calls to the target's statics by matching the `fn ==` handler addresses, and keep `#include "mod/<mod>.c"` so the
  file's own types are used.

- **Constant-count fill loops with the counter/pointer swapped.** When a function has many identical fill loops
  (`lwc1`/`swc1` from a stack vector, `paddub v1, zero, zero`, `a0 += 0x10`) and every loop after the first has the
  counter and pointer registers swapped, write one `static inline` helper that walks the pointer
  (`for (i = 0; i < 9; i++, q++)`, s32 `i`) and pass the source as a `Vec4f` local by `&p` (not `f32 p[4]` with a cast).
  That also fixed the `li a1` / `addiu a3` order before the next call (b495:01E02140).
- **Plain `dk try` stays near 99% when the function calls a static defined above it** in the module file (the original
  skips reloading argument registers the static leaves alone). Check with `tools/mod_infile.sh` and `work/fulltry.sh`,
  then `dk accept` (b495, b544).

- **`p[k % 4]` in a loop:** when the original computes `g + (k%4)*16` once and reads at fixed offsets from it, index
  the array with an s32 temp (`k = i % 4; g->p[k].x ...`). A `Vec4f *s = &g->p[i % 4]` pointer adds an `addiu` and
  swaps the `addu` operands (b258:01E01A70).

- **Two float constants loaded in the wrong order (`$f13` before `$f12`):** put only the first argument in a local in
  its own nested block, `{ f32 r = 1.0f; f(p, r, 0.05f); }`. Declaring `r` in the enclosing block moves a later call's
  constants instead. It only shows in the file, so check with `tools/mod_infile.sh` (b113:01E03F50).
- **Calling an in-file static that takes a float from a standalone work file:** give its link alias a prototype
  (`extern s32 b113_01E00280(void *, void *, s32, f32);`); a no-prototype extern promotes the float to double.

- **`(u32)(p + t * (f32)(q - p) / n)` at -O2 with the `mul.s` too early:** the original converts the quotient, then
  `p`, then multiplies. Put the quotient in a float local first: `d = (s32)(q - p) / n; x = (u32)(p + t * d);`
  (b299:01E03B30).

- **-O2 scene manager with every saved register rotated (the parameter `g` coloured last, `$s3` not `$s0`):** no
  declaration order fixes it. Copy the parameters into locals and keep the copies with `#pragma opt_propagation off`
  (reset after): `static s32 f(Scene *arg0, s32 arg1) { Scene *g = arg0; s32 code = arg1; ...`. Either half alone does
  nothing; copying only `g` leaves the two parameter moves swapped (b035:01E02070).

- **A call-free `if (..) n = 2; else n = 2;` loop limit with a sign-extend in each arm and in the limit register:**
  assign the arms to the previous loop's counter and copy it: `if (..) i = 2; else i = 2; cnt = i; for (i = 0; i < cnt; i++)`.
  Arms on the limit merge the sign-extends; arms on `i` with another loop counter swap counter and limit (b433:01E01850).

- **A clamped count and a strength-reduced array pointer swapped (`$s2`/`$s3`), unmoved by declaration order or
  counter names:** read the field twice in the `?:`, `n = e->seg > 36 ? 36 : e->seg;` (still one load), not
  `n = e->seg; n = n > 36 ? 36 : n;` (b040:01E05BD0).
- **Byte loads before an alpha fade landing in permuted `$a0`..`$a3`:** compute the difference into a fresh block local,
  `{ s32 d = e->max - e->life; ... d * (e->c.a >> 4) ... }`; reusing a local doesn't work (b040:01E05BD0).
- **`t == 0x75 || t == 0x76 || t == 0x77` folded into `addiu` + `sltiu` at -O4 where the original has `bne` chains:**
  a `switch` gives `beq` + `b`; build the function at -O3 instead (b060:01E00080).

- **-O2 loads in a different order from the expression's operands** (`len`, then `rad`, then `h` for
  `rad*rad*(1 - h*h/(len*len))`): put the fields in block locals in load order,
  `{ f32 l = e->len; f32 q = e->rad; f32 hh = e->h; r = q*q*(1.0f - hh*hh/(l*l)); }` (b176:01E02820).
- **A masked byte difference with an `andi 0xFF` into a temp before the `and`:** use a block-local u8,
  `{ u8 t = e->max - e->life; age = t & e->mask; }`; casts in one expression never give the first `andi` (b176:01E02820).
- **`#include "mod/<mod>.c"` in a work file can hide a real-file clash:** statics defined below the function become
  visible, so the standalone try matches but the in-file build reports CLASH / "redeclared". Call those through
  `<mod>_<VADDR>` aliases (b770, b089).

- **An int → float conversion the original delays (`mtc1` early, `cvt.s.w` + `div.s` late) with permuted float
  registers:** declare the values `f32` and divide each in its own statement (`x /= 20.0f; y /= 20.0f;`) before use;
  `(f32)y / 20.0f` in the expression stays off (b493:01E02200).

- **Down-counting loop with `slti $at, i, 0` where yours has `bltz`/`bgez`:** write `i > -1`, not `i >= 0`
  (c516:01E018D0).
- **Three float loads then three stores, where yours alternates:** copy the three fields as one struct
  (`s->t[i + 1].p = s->t[i].p` with a Vec3 member); float locals schedule it wrongly (c516:01E018D0).
- **-O1 setup-loop counter wanting `ot`'s register:** give the setup loop its own counter; `ot` is dead in that
  branch, but a counter shared with a later loop can't take its register (b011:01E050B0).

- **Hoisted packet-vertex addresses in `s0..s3` after the loop test, the loop pointer and counter pushed to `s4/s5`:**
  set the vertex pointers between an explicit guard and a do-while: `i = 0; if (i < n) { q3 = &pk.v[3]; ...;
  do { ... } while (++i < n); }`. Set before a `for`, they land before its test; inside the loop they become compiler
  temporaries. Use `i < n` (`n > 0` gives `blez`) (b131:01E053B0, ShFx_Rcore).

- **Two equal float constants in the last two arguments of a module static, the original loading the last first
  (`mtc1 $zero, $f15; mov.s $f14, $f15`):** call it through a prototyped alias
  (`extern s32 b719_01E01ED0(void *, s32, f32, f32, f32, f32);`) instead of its static name (b719:01E02DF0).

- **`f(p, 2.0f, 0.1f)` with `$f13` loaded first, where a local for the first argument doesn't help:** put the last
  argument in a nested block local, `{ f32 q = 0.1f; f(p, 2.0f, q); }` (b015:01E03460).
- **An int field plus a float with `add.s` operands swapped:** write the compound assignment `o->ang += 8.0f;`
  (b089:01E00A30).
- **An s32 field reloaded narrow (`lwc1` to convert, `lh` for `% 360`) where yours CSEs into one `lw`:** read the
  narrow use through an s16 union member, `o->a.i = (f32)(s16)(o->a.h % 360);` (b089:01E00A30).

- **Packet 8 bytes above where yours lands, the 8-byte gap after it instead of before:** large locals sit on 16-byte
  boundaries, so the packet must be 8 bytes into a bigger object: `struct { u64 dma; Pkt gif; } pkt; p = &pkt.gif;`
  (b494:01E01A90).
- **The parameter-copy trick (b035) works at -O4 too:** copy the parameters into locals under
  `#pragma opt_propagation off`, then re-run a declaration-order search (b494:01E01A90 went 458 → 603/603).
  Under that pragma every constant-bound `for` gets an entry guard (`slti`/`beqz`), so the trick doesn't suit
  functions with setup loops whose original has no guard (b594:01E02EC0).

- **Temps in `$a0`/`$a1` around `jal func_001A23B0` where yours uses `$a2`/`$a3`:** call `func_001A23B0(x)` by name
  instead of `(u32)x`. With the cast the compiler keeps the next call's arguments in `$a0`/`$a1` across the helper; a
  real call frees them (b000:01E04540; b000's other functions call it the same way).

- **u8 → float through the unsigned path with the constant loaded before the conversion:** put the byte in a `u32`
  local, convert into a float local, then use it (`a = u; a = rad(360.0f * a / 255.0f);`). A product with reversed
  operands gets its partial product in its own statement (b172:01E03670).
- **A u8 table counter stepping by 3 with an `andi` on each index:** write three `k++` (two in the table reads, one
  bare), not `tbl[(u8)(k + 1)]` and `k += 3` (b172:01E03670).

- **-O4 setup loops with counter and strength-reduced pointer swapped (s2/s3) in all but the first:** give every setup
  loop its own counter (`i`, `j`, `k`, `m`); sharing one, or splitting only the first, stays off (c548:01E02720).
- **`f(p, 0.0f, 0.0f)` with `mov.s $f13, $f12`:** `{ f32 r = 0.0f; f(p, r, r); }` (c548:01E02720).
- **`rand() % 0x10000` as `andi` plus a dead `addiu x, x, 0`:** the signed modulo; keep the variable `s32` (a `u16`
  adds an `andi`) (b103, b540).

- **A value loaded before a struct-copy loop (`lw $a3` + `nop` ahead of `lq`/`sq`) and stored after it:** copy it to
  its own local first (`t = tex; ... g->pts.tex = t;`); reusing a loop counter disturbs the loop (c512:01E015C0).
- **A setup loop's counter coloured last (after the strength-reduced pointers):** share the first loop's counter `i`
  (the reverse of the c548 tip; try both) (c512:01E015C0).
- **Two stack vectors with `.y`/`.z` addresses in saved registers and a frame 0x20 bigger than yours:** `f32 v[3][4]`,
  extending the `v[2][4]` tip (b732:01E02610).
- **Float argument load order can depend on the whole function:** in c531:01E01040 deleting a dead `one = 1.0f;` moved
  which of three identical calls loads `$f13` first.

- **A module whose float-cast temps sit in different argument registers from its matched copies elsewhere**
  (`$a0` or `$a1` where every other copy has `$a2`, around `jal fptoui`/`fptosi`): the module was compiled in a
  different warm state. Try its whole module cold or after a one-argument helper by adding it to
  `config/mod_warm.txt` (`0` or `1`); keep it only if the whole module still matches. b000 is cold, b005 and b007
  are level 1 (LkEFF_SortLaser b000:01E03B80 / b007:01E02FC0, b005:01E003A0 / 01E027F0).

- **Float argument order can differ between `tools/mod_infile.sh` and the real build** (b467's `func_001033D0`
  calls); search block-local forms with `work/fulltry.sh` directly (about a second per try).
- **A struct temp that belongs after the inline-return temps in the frame:** write the copy twice
  (`ca[0] = a[0]; ca[1] = a[0];`) so the CSE temp goes last; a named temp sits in declaration order. Locals with an
  explicit `aligned(N)` go after all temps (b847:01E02370).
- **Temps after a call in `a3`/`a2` where yours get `a1`/`a0`, with a `jal func_001A22C0` (fptosi) later in the
  function:** write that conversion as a plain cast, `(s32)(10.0f * e->radius)`, not an explicit `func_001A22C0(...)`
  call. In the warm build the compiler's own fptosi call counts as reading a0/a1, so they stay live back to the last
  call's arguments and every temp in between skips them. Dropping the then-unused extern can move float loads, so
  try with and without it (b486:01E02E80, b540:01E03160, b157, b168, b263; small repro in work/wall/).
- **A module static's argument order or delay slot off (`$f13` before `$f12`, `a3` before `a2`) and block locals don't
  help:** call that one site through an alias even when the static is defined above: a block-scope prototyped
  `extern s32 <mod>_<VADDR>(void *, ...);` for float arguments, a no-prototype one otherwise. Fixing one call can move
  a sibling call, so search combinations with `work/fulltry.sh` (b028:01E03CE0, b144:01E03740).

- **A struct-returning static whose result the original builds straight into a stack local** (`addiu a0, sp, X`, no
  copy after the call): declare the local with the static's return type and assign `c = f(...);`; pass array rows as
  `&g->tr[3][0]`, not a casted `g->tr[3]` (b080:01E03090).
- **A draw-loop index recomputed every iteration (`sll v0, i, 6; addu s2, g, v0`) with the counter reset in one
  branch:** the original reuses the outer counter for an inner loop (`for (i = 0; i < 10; i++)` inside the slot loop)
  (b080:01E03090).
- **`0.1f * i` with the conversion in `$f1` and `mul.s $f0, $f0, $f1`:** `{ f32 t = i; g->f = 0.1f * t; }`
  (b080:01E03090).

- **A local table copied from module data right after the first call (`jal func_00207500` before the `lq`/`sq` copy)
  where yours copies it in the prologue:** assign it as a statement after the call (`ot = func_00207500(); tbl = D_...;`),
  not in its declaration, and declare it first among the stack locals (b455:01E05AA0).

- **Where a prototyped alias's `extern` sits can change float argument order:** in c525:01E033D0 it matched only
  declared inside each call's own block; one shared declaration at the top swapped the `$f12`/`$f13` loads again.

- **A `?:` clamp's variable spilled after every declared local, whatever the declaration order:** the `?:` makes it a
  compiler temp. Write `if (n > 36) { n = 36; } else { (void)n; }` (the else arm keeps the original's `b`); its slot then
  follows declaration order (b761:01E05F70).
  Contrast: an -O2 clamp `li n, K; b L; nop; L:` (a branch straight to the next instruction) is the plain
  `n = n > K ? K : n;`; the if/else form gives an extra `nop` there (b462:01E04230).

- **A difference kept in a saved register across a call (`m - k` for an alpha ramp):** write it inline in both
  statements, `(f32)(m - k)` and `(f32)(m - k - 1)`; a local `d = m - k` swaps its register with a strength-reduced
  pointer (b405:01E03430).

- **`jal func_0017B380` / `func_001A2918` / `func_001A3090` triples with `lui 0x3FE0; dsll32`:** double maths on a u8,
  `c[k] *= 0.5;` (MWCC calls `_d_utod` by name; it is in config/linker_syms.txt). `c = c * 0.5` keeps the constant in
  a saved register instead (c056:01E015A0).

- **A setup loop that writes past an array into the fields after it** (`for (k = 0; k < 30; k++) size[k] = 40.0f;`
  over a 20-entry array and the joint ids behind it): model the overlap with a union in the struct,
  `union { f32 size[30]; struct { u8 pad[0x60]; s16 jA, ...; } j; }`, so no index is out of bounds (b425:01E020C0).

- **A value used both in an argument and as a `switch` selector, its register swapped with a strength-reduced temp:**
  write the expression in both places (`(u8)(k % 3 * 2 + (k >> 2) * 4)` and `switch (k >> 2)`) and let the compiler
  share it; a named local keeps the swap (b078:01E05C90).

- **An int stepping alongside a loop counter (an angle `+= 0x1000`) with counter, value and pointer in rotated saved
  registers:** give the loop its own counter, declare the stepped value last, and set it in the `for` header:
  `for (k = 0, ang = 0; k < 4; k++)` (b273:01E02BB0).
  A second copy of such a loop in the same function wants its own block-scoped variables,
  `{ s32 n, ang2; for (n = 0, ang2 = 0; n < 4; n++) { ...; ang2 += 0x1000; } }` (b576:01E02BC0, b621, b105).

- **`daddiu $v0, $zero, K; subu $v0, $v0, $sN` stepping by a constant in a loop from a constant start:** the
  compiler's start value for a strength-reduced `i * M`, not `K - i`; write the plain product (`g->a = i * 15;`)
  (c030:01E00080).
- **-O2: a slot address the original rebuilds after every call where yours keeps it in a saved register:** write the
  call's argument as raw bytes, `(u8 *)g + idx * 0x58 + 0x4D8`, so it shares no subexpression with the field stores
  (b649:01E043A0).

- **`beqz $s0` on an s16 counter where yours sign-extends first:** write `if (m)`, not `if (m != 0)` (b746:01E045A0).
- **A scene manager's slot count in the last saved register, below the loop counter and the id parameter:** it is the
  setup loops' counter reused (`k = 0;` at the top, `k++` in the draw loop); give the step and draw loops their own
  counters (b215:01E02E50, 650 → 685).

- **Screen-UV clamp block (`(0x6BF8 - x) / -16.0f - 0`, clamped to 0..640 / 0..480) with the zero and -16.0f
  registers rotated:** the zero is a named variable kept by `#pragma opt_propagation off`. Write `z = 0.0f;` at the
  start of each corner's block, then `s = 0x6BF8 - v.x; s /= -16.0f; s -= z;` and clamp with `if (s < z) s = z;`;
  declare `z` before `s`/`t` and give the bottom corners their own pair. A literal `- 0.0f` folds away
  (b490:01E01260, b504:01E01980, b361:01E01140).

- **-O1 `lhu $a1, t` before `addiu $a0, g, K` in `func_001031C0(&g->x, g->t)`:** declare the callee
  `(void *, u16)`, not `(void *, s32)` (b059:01E05540).
- **Two stores to one field with the second in a call's delay slot:** the source writes both before the call,
  `g->hB8 = 4; g->hB8 = 0; f(...);` (b207:01E03C40).

- **A stack vector's base address kept in a saved register** (`addiu sN, sp, X` used for the `.x` store and as a call
  argument): it is element [1] or later of a `Vec4f` array (`Vec4f p[2]`, pass `&p[1]`). Element [0] and plain
  `Vec4f` locals only get their `.y`/`.z` addresses kept; `f32 v[4]` arrays get neither (b104:01E03E30, b129:01E04B90).
- **Two float variables in swapped registers in the second of two similar blocks:** swap which name holds which value
  in that block (b104:01E03E30).

- **No `jal` for a small static handler in a scene manager's step loop:** the compiler doesn't inline on its own; the
  original wrote the handler's body in the `fn ==` branch (a float-pair handler in a block with its own `f32` locals)
  (b570:01E03020, b297:01E02650).

- **Frame layout with `aligned(N)` locals** (c606:01E00080, c603:01E00920): plain locals whose size is a multiple of 16
  go first, in declaration order; locals with an explicit `aligned(N)` form a group at the top, each rounded up to 16,
  filled top down (the last declared highest). So a packet 8 bytes above yours can be just
  `Pkt pkt __attribute__((aligned(8)))` when its size isn't a multiple of 16; a 12-byte array at an 8-mod-16 address
  just below it means both are `aligned(8)` and the packet has a trailing `u64`. The b494 tag-plus-packet struct can
  make the compiler keep `&pkt.gif` in a saved register; try plain `aligned(8)` first.
- **After the parameter-copy trick, assign the copies as statements in the right order** (`mode = arg1; o = arg0;`
  put the `o` move in the `jal` delay slot; an initializer didn't) (c606:01E00080).
- **Screen-UV blocks with `cvt, cvt, div, div` and no `sub.s`:** the plain split form,
  `u = 0x6BF8 - x; v = K - y; u /= -16.0f; v /= -16.0f;`; the named-zero form is only for originals that subtract a
  zero (b215:01E02660).
- **Spill area 0x10 too big, unused float slots before the first float spill and an unused int slot between two
  spilled ints:** put `__attribute__((aligned(8)))` on the first spilled s32 local (the `func_00207500()` result); it
  pushes the float spills up (b847:01E02370, b073:01E03E70). Spilled parameters 4 bytes too high: `aligned(8)` on the
  later one (b706:01E050E0).
- **Packed xyz u64s copied with `addiu reg, sp, X; ld; addiu; sd`:** a bitfield struct type for both the local array
  and the vertex member, copied whole (b706:01E050E0).
- **`add.s fd, K, prod` where the original has `add.s fd, prod, K`:** put the literal in a local (`rr = 25.0f;`)
  (b378:01E02440).
- **An extra `nop` before the epilogue after the last loop:** the setup path is the `if` arm of an if/else, not an
  early `return` (b378:01E02440).
- **A float loop invariant the original recomputes at every use** (`lui/ori/mtc1` + `add.s` before each call where
  yours hoists it): put the constant in a named local, `w = 0.3f; ... (t + w) * f()` (b130:01E01E60, b499:01E038F0).
- **The aligned group is packed top-down at each object's own alignment**, not in 16-byte slots: a 4-byte colour at
  top-4, then `pk[0x90] aligned(8)` 8 bytes lower (b018:01E01760, b130).
- **A pointer walker assigned before a NULL test in the wrong saved register:** test the field itself and assign the
  walker in the `for` header, `for (list = obj->frames[i]; *list > 0; list++)` (b029:01E00EF0).
- **A family member whose "structure is wrong" may only be built at another -O level:** try all four before reworking
  (b099:01E04C30 is b029:01E05AA0's C at -O2).
- **A u8 local spilled with `sb`/`lbu` (no `andi`) while a sibling stays in a saved register with `andi`:** give the
  callee's parameters u8 types in its prototype (`(u8 *, u8, u8)`) (b262:01E00F50).
- **Copy only the parameter that needs it** under `opt_propagation off`: copying a u16 parameter too adds an `andi`
  into a saved register (b179:01E03940 copies only `obj`).
- **Before the parameter-copy pragma, try `s32 arg0` with a cast local and no pragma** when `g` must take s0
  (`static s32 f(s32 arg0, s32 id) { T *g = (T *)arg0;`) (c501:01E00910, b521:01E01BD0).
- **-O3 bitfield loads (`q.x`, `q.y`) in each other's temp registers:** read one into a u16 local first (`py = q.y;`)
  (b015:01E008F0).
- **A struct copied as four words where yours copies halfwords:** its padding is `s32 pad[2]`, not `u8 pad[8]`
  (b521:01E01BD0).
- **Arc-band draw (`IWMagicCircleGT4_*`) with the flags `andi` between the span's `dsll32`/`dsra32`:** test
  `(flags & 0xF)` inline in the loop, not through a mode local; write `t = span + a` (c061:01E01100, b390:01E015E0).
- **A missing `nop` after an `mtc1` in an if/else that sets a float, with a stray `addiu; sw` at the join:** reuse an
  existing float temp for the value instead of a new local (b115:01E02A10).
- **Delay slots filled from the fall-through all over a function where the original leaves `nop`s:** look for a `?:`
  that compiles to `movn`; written as an `if`, all the nops come back (c030:01E01510).
- **Float argument registers swapped only in the full build:** drop a block-scope `extern` that repeats a
  `functions.h` prototype (c030:01E01510, `func_00106DD0`).
- **Float saved registers or divisions in the wrong order:** put a shared int subexpression (`40 - g->left`) in its own
  s32 local (b351:01E068F0).
- **Loop angles copied with a fresh sign-extend into new saved registers:** there is no stepped variable in the
  source; pass `ra + i * 18` directly and let strength reduction make the copies (b357:01E03420).
- **The named-local constant also fixes `mul.s` operand order** (`nx = 20.0f; ... 2.0f * o->f48 * nx`) (b215:01E01A70).
- **Before reworking a hard draft, look for twins by its real name** (b004's B004PAINT_RAIN was b130:01E01E60's C).
- **One angle passed to several calls in a row, kept in a saved register and sign-extended before each call:** an s32
  local with an s16 prototype parameter (`n = o->ang + j;`); a copy sign-extended again before a divide is an s32
  local cast at the use, `(s16)b / 160` (b443:01E01EA0).
- **A field converted before a call into a saved float register (`cvt.s.w $f21` in the jal delay slot) where yours
  converts after:** copy a parameter (`mode`) into a local under `opt_propagation off` (c059:01E03610).
- **`b test` where yours has an entry guard, plus loop-invariant ints spilled after the declared locals:** write the
  bound and divisor inline (`k < n - 1`, `/ (n * 3)`), not as named locals (b134:01E011E0).
- **Look for twins by shape comment too** (`grep -rn "shape .*burst" src/mod`): b108:01E03130 was b034:01E05A90's form.
- **A strength-reduced counter and a pointer local swapping saved registers:** drop the pointer locals and write the
  address inline at each call (`pa + (k - 1)`) (b500:01E047C0).
- **A "dead" struct copy into the stack before a draw call (never read back):** it is the tail of the packet the call
  receives; take the packet type from a matched sibling (c605:01E028C0 from c602:01E01620).
- **A stack-buffer address hoisted into a saved register for a call in a loop:** the argument is a member at a non-zero
  offset of a larger stack struct, often merged with a neighbouring buffer (`&pk` and `pk.xyz`) (b506:01E01BA0).
- **A `?:` clamp's spill slot after a later loop counter's:** drop the later loop's variable and reuse an earlier
  loop's counter (b379:01E046B0).
- **A float constant stored as an int `sw` and also kept in a saved float register:** a chained assignment,
  `f = o->f34 = 50.0f;` (b756:01E02360).
- **Check twins for each block of a hard function, not just the whole function** (c534's UV block was c560's uv
  inline); a spilled s32 parameter 4 bytes too high takes `aligned(8)` itself (c534:01E027F0).
- **A stepped value with an `sll` inside the loop** (`addiu s3, zero, 0x3C ... sll v0, s3, 4 ... addiu s3, 0x3C`):
  write `(i * 60 + 60) * 16`; `(i + 1) * 60 * 16` folds into `* 960` (b617:01E06210).
- **`beqz i, A; b B` with arm A first and an extra `b`** where an if/else gives `bnez` → else: a single-case
  `switch (i) { case 0: ...; break; default: ...; break; }` (b617:01E06210).
- **A field-by-field copy of a stack vector onto itself** (`swc1` then `lwc1`/`swc1` of the same addresses before a
  by-value call): the source has `c.x = c.x; c.y = c.y; c.z = c.z;` (b443:01E04160).
- **Argument registers set in the wrong order around a static call:** cast the second argument too
  (`(Emit_b000_01E01140 *)&g->emit`) (c625:01E02DA0, b634:01E03110).
- **An unused local can change scheduling** (b634:01E03110 keeps an unused `s32 k;`); try removing leftovers last.
- **A beam with no `jal func_00109A70`, only `lwc1`/`swc1` x/y/z copies:** write the vector copies field by field
  instead of calling the copy helper (b108:01E03430).
- **Temps after a call skip a0/a1 before a `jal func_001A23B0`:** the conversion is a plain `(u32)` cast (the b486
  effect for fptoui); the reverse of the b000 tip, so try both (c401:01E00080).
- **`li v1, 1` should come before an index load into a0:** assign the index inside the first subscript,
  `g->slot[a = g->next].used = 1;` (c401:01E00080).
- **-O4 manager keeping `&q` in a saved register across `func_001F5F90(u, &q)` / `func_00103DB0(&q, ...)`:** assign the
  pointer inside the first call (`func_00103DB0(pq = &q, ...)`); declare a second held pointer (`f32 *pz`) before it
  (b753:01E020A0).
- **A ring set-up with `addiu a0` before the last `mtc1` for two equal radii:** `r = 18.0f;` right before the call,
  passing `r, r` (b001:01E044C0).
- **`lbu a1` before `paddub a0` for a static's arguments:** give the byte parameter a u8 type in a block prototype
  (`(void *, u8, u8)`) (b099:01E02A90).
- **`(r = &pool[i])->life = x;` loads the field before building the pointer:** split it, `r = &pool[i]; r->life = x;`
  (b099:01E02A90).
- **`slti v0, t, K; bnez v0` with `n = 2` in the delay slot, then `b join; n = 1`:** flip the test,
  `if (t >= K) n = 1; else n = 2;` (b132:01E06AC0).
- **Whether a static's float arguments load in order can depend on how neighbouring static calls are written:** search
  name/alias combinations across nearby calls with `work/fulltry.sh` (b401:01E02FD0). Float arguments loaded
  `$f13, $f14, a1, $f15, $f12`: declare the locals bare and assign them in reverse order before the aliased call
  (`f32 p; f32 s; s = 18.0f; p = 0.1f;`) (b013:01E04510).
- **`f(p, 0.0f, 0.0f)` with `mtc1 $zero, $f13; mov.s $f12, $f13`:** `{ f32 x = 0.0f; f(p, x, 0.0f); }`, the opposite of
  the c548 `(p, r, r)` case (c508:01E04B50).
- **A stack slot used directly in the setup and through a saved register in the main path, in a frame 0x10 smaller
  than an honest layout:** the original may index one past an array onto the next local (`Vec4f w[2]; s32 tx[4];`
  and `w[2]`). MWCC never shares slots between block-scoped locals, so no honest form gives both. Look for a sibling
  with its own slot first (b613:01E04010); the LkEff_SetCocoon managers (b220/b366/b409/b277/b055:01E03400) keep the
  original's `w[2]` with a comment.
- **Kept addresses:** a constant non-zero offset into a local (array element or struct member) used twice goes
  through a saved register from its first use; a plain local at offset 0 never does.
- **-O1 saved registers follow declaration order** (variables sharing a register take one slot); reorder declarations
  first (b200:01E05B40, 701 → 763). An -O1 u8 argument goes inline as `(u8)(expr)`, not through a u8 local
  (b002:01E05FE0).
- **A `dk try` that never returns:** look for a negated float compare (`if (!(f(x) <= 3.0f))` hung mwccps2 at -O4;
  `> 3.0f` compiled and matched) (c059:01E00FB0).
- **`daddiu $sN, $zero, K` where yours has `addiu`, for if/else-picked constants kept across calls:** the locals are
  `u8` (c547:01E02700).
- **A main-program call with its last argument loaded first:** the argument had a cast against an int parameter in
  functions.h; a block-scope prototype taking `void *` with no cast restores the order (c031:01E00D00).
- **Float arguments loaded `$f13` first right after an if-block join** (the bc1t delay slot holding the second
  constant's `lui`): declare the second constant as a block local before the `if` (b140:01E037A0).
- **An `||` of two ranges where the original uses `$at` for every compare:** write the upper bounds with `<=`
  (`t <= 77`, not `t < 78`) (b140:01E037A0).
- **Float-argument order flipping across a whole function:** search the forms of every two-float call together (a
  random search over block-local/alias choices scored by fulltry found b419:01E02B40 in 300 tries; one call at a time
  does not converge).
- **14-bit UV bitfields scheduling wrong:** name the scaled coordinate (`x = kind % 4 * 32; ->u = x << 4;`), not the
  cell index (c402:01E00080).
- **A constant set once in an unexpected argument register and used for one store** (`li a1, 1` then `sh`): it is
  really a later call's argument; read which argument registers each `jal` expects first (b079:01E04240).
- **The second of two zero-float-pair calls copying `$f15`→`$f14` when no argument form fixes it:** move the zero
  assignments (`h = 0.0f; y = 0.0f;`) to the top, right after `rv = 0;` and before the NULL checks (c604:01E037D0).
- **No block-local form moves a zero-pair float argument order at all:** the locals are propagated away; put
  `#pragma opt_propagation off` around the function so the c508 form takes effect, then rewrite any loop that gains an
  entry guard as a do-while (c027:01E00C50).
- **`and v0, v0(field), sN(local)` with the operands swapped:** re-read the field (`n - (o->step & o->mask)` with
  `n = o->mask` already loaded) (b132:01E02690).
- **dk try's "built without optimisation" hint can be wrong** when every delay slot is a nop; sweep the levels
  (b125:01E01EE0 was -O2).
- **Look up a libgcc double helper's real name before choosing the operator:** `func_001A2858` is `dpadd`, `0x1A2918`
  is `dpmul` (config/linker_syms.txt); b573:01E03C70's `v.y = v.y + 2.5;`.
- **A static's float argument loaded from a field before an int stack argument:** a no-op cast,
  `f(&o, tex, (f32)g->r)` (b118:01E03A20).
- **Prefer named fields in local types over writes through pad arrays or pointer casts** (`*(f32 *)emit.pad28`,
  `*(Vec *)&v`, `*(u8 *)&e->start`); `(u8)e->start` gives the same `lbu`. Changing types can flip float argument
  orders elsewhere, so rerun floatsearch after (b395:01E03D10, b166:01E05400, b213:01E04C90).
- **A stack-array load and a constant hoisted above a run of field stores, the store at the end of the run:** copy the
  value into a block local first, `{ s32 t = tx[0]; o->x = o->y = o->z = 0.0f; o->scale = 10.0f; o->texture = t; }`
  (b127:01E04750).
- **After floatsearch, revert its changes one at a time and keep only those whose revert breaks the match** (its random
  phase leaves noise forms; c534:01E03D50 went from 12 changed calls to 9).
- **Big register rotation in a scene manager:** a greedy search renaming each loop's counter in turn (i, k, j, m, n),
  scored in-file, found b154:01E026A0's fix in about 50 tries (example script work/greedy_counters_example.py).
- **A whole-vector copy computing the source address before the destination:** declare the local with the
  destination's struct type so the copy is a plain assignment; cast the other users instead (b106:01E05580).
- **An `sh` store before the argument moves where it belongs in the `jal` delay slot:** pass the shared
  `u8 buf[0x90]` uncast, not `(void *)buf` (b357:01E05340).
- **Two zero float arguments loaded `mtc1 $zero, $f15; mov.s $f14, $f15`:** `(..., 0.0f, z)` with `f32 z = 0.0f;`
  (floatsearch missed it) (b138:01E03C60).
- **A stack address at or above the frame size passed as an output buffer** (sp+0xD0 in a 0xD0 frame): the original
  indexes past an array at the top of the frame; no honest layout reproduces it (b644:01E04740 keeps `v[3]` past
  `Vec4f v[2]` with a comment, like the LkEff_SetCocoon managers).
- **A hoisted loop-invariant with `andi aN, sN, 0xFF` at each call:** a u8 parameter in a block prototype and the
  value passed uncast (`j & 1`); a `(u8)` cast folds the `andi` (b526:01E05E90).
- **`jal fptosi` then `andi 0xFF` for a float byte argument:** `(u8)(s32)s`; `(u8)s` calls fptoui (b096:01E00AA0).
- **A ring's closing-element copies computing the source address first, with CSE'd `(sp+K)+k*48` addresses:** declare
  the ring as a 2D array of a small struct (`V3 ring[37][4]`, copies `ring[36][j] = ring[0][j]`) (b033:01E04020).
- **Texture-setup outputs 8 bytes past the packet:** put the packet and the `func_00208800` out-arguments in one
  `aligned(8)` local struct (b033:01E04020, as b010's Afx04).
- **Many float-constant calls in a row:** search them in order, scoring each choice only by the differing words up to
  that call's `jal` (a call's load order depends on earlier calls, not later ones); this converged where floatsearch's
  whole-function greedy stalled (b037:01E04FB0 39 → 8 words; work/floatseq_example.py).
- **A whole-function search rejects a float-order fix that flips later calls:** `floatsearch.py --seq` keeps it and
  repairs the later calls one at a time (closed b364:01E041E0 and b274:01E02B40 after 2,000 stalled tries).
- **An if/else in a setup loop with an extra `nop` after the else arm's store:** end the first arm with `continue`
  instead (`if (i == 0) { a[0] = 0.0f; continue; } a[i] = ...;`) (c059:01E04420, 983 → 995).
- **A saved-register rotation no order of plain locals fixes:** include the cast-initialised scene pointer
  (`Scene *g = (Scene *)arg0;`) in the declaration-order search (c537:01E02EB0).
- **A slot index read from a field reloaded and re-multiplied before every store:** read it into a local first,
  `k = g->count;`, then index `g->shell[k]` (b608:01E05920).
- **-O2 `x += 0.0f` / `x -= 0.0f` kept as `mtc1 $zero; add.s`:** a float local set to 0.0f (a literal folds away)
  (b398:01E05E50).
- **An -O2 Lk manager with the `ot` copy (`paddub a0, s1`) after the address arguments:** call the draw statics
  through no-prototype aliases (b523:01E046E0, b025:01E045A0).
- **One saved register short in an -O4 manager with zero-inits at entry missing:** the original's last arm re-tests a
  range the outer test already covers (`else if (t >= 0x12)` where `else` would do), so the compiler keeps `m = 0;`
  at entry (c062:01E04470).
- **-O2 range tests:** `slti $at, t, K; beqz` came from `t < K` (try `<` first at -O2) (b843:01E06910, b561:01E03280).
- **-O1 element index built from `$zero` for its first use** (`paddub sN, zero, zero; sll v0, zero, 3`): the source
  assigns the index just before use, `i = 0; f(&g->flear[i]);` (b200:01E06740).
- **-O1 negation through one element address:** `g->quad[k].rot[2] *= -1;`, not `x = -x` (b200:01E06740).
- **A switch compare `beq` that jumps straight past the switch** is an empty `case K: break;` (b497:01E05190).
- **A zero float pair loaded last-first that no block form fixes:** both zeros as function-scope locals assigned before
  the function's first statement (`y = 0.0f; h = 0.0f;` ahead of `ot = func_00207500()`) (c541:01E03B60).
- **-O1 int temp in `$a1` where the original has `$a0`:** the reused variable is a later call's second argument and
  gets coalesced; give the expression its own block local (b177:01E01E90).
- **One float local reused in several switch cases, landing in `$f1` in one of them:** give that case its own local
  (b033:01E05470).
- **Vector fields stored to the stack and reloaded at once, where yours keeps them in registers:** the vector is an
  element of a local array whose address is taken (`Vec4f w[2]` with the step in w[0], the by-value point in w[1])
  (b112:01E026C0, 474 → 1151). A call's output vector with its address in a saved register is w[1] of such an array
  (b758:01E04D00).
- **Rotated registers in one of several identical copy loops:** give that loop its own pointer local as well as its
  own counter (b531:01E02830).
- **`x = (s32)(x * -1.0f)` with the `mul.s` operands swapped:** `x *= -1.0f` (b173:01E04BF0).
- **Search scripts for large managers:** `work/greedy_ctr_ft.py <mod> <func> <file>` (greedy loop-counter rename) and
  `work/declperm_ft.py <mod> <func> <file> "<decl>"...` (every order of the given declarations), both scored by
  fulltry (b716:01E06320, b370:01E062B0).
- **Two stack vectors at sp+X and X+0x10 with a 4-word `lwc1`/`swc1` copy between them (yours `lq`/`sq`):** one
  `Vec4f w[2]` and `w[1] = w[0];`, even when w[1] is not read later (b370:01E062B0).
- **A `sw` of a float constant then `mtc1` of the same GPR into a `sub.s`:** read the just-stored field back,
  `f[0] = K1; f[1] = f[0] - K2;` (b579:01E04C80).
- **An s32 masked into `$v0` then moved to `$a0`, where yours masks straight into `$a0`:** two statements,
  `ang = (s32)(...); ang &= 0xFFFF;` (b483:01E00080).
- **A loop-head `nop` that comes and goes:** loop labels are 8-aligned, so it follows the instruction count earlier
  in the function; fix earlier differences first (b635:01E044B0).
- **A loop's counter and pointer swapped with no fix inside that loop:** rename the counter of a different, earlier
  loop in the same branch (each counter name is one web per function) (b369:01E04A00).
- **Constant stores scheduled above a cast-conversion call** (colour bytes before `jal fptoui` where the original stores
  them after): `(void)alpha;` right after `alpha = (u32)(...);` keeps the cast's register effect (b150:01E00080).
- **Indexing with `k + 5` in a loop strength-reduces where the original recomputes each time:** `n = k + 5;` right
  before the first use, index with `n` (b583:01E05670).
- **Two locals from different points in the function at one stack slot:** one variable reused (block-scope locals get
  separate slots), e.g. a texture-id buffer later used as a position output (b773:01E049E0).
- **A copy chain through `addiu sN, sp` pointers:** the copied vectors are one array (`Vec4f p[3]`); a vector using
  direct sp offsets stays separate (b598:01E05E60).
- **The ot copy lands last in an -O2 manager even through no-prototype aliases:** drop every cast in the alias calls
  (c621:01E03FA0, 36 → 5 words); `u32 ot` did better than `s32 ot`.
- **A bolt loop's counter and walking pointer rotated:** index `pts[i]` / `pts[i + 1]` directly and drop the pointer
  (b853:01E05820). Loop-name search: work/loopnames.py.
- **Parameter g spilled to a low stack slot and reloaded before every use (the "spill wall", about 71 single-function
  modules at 01E00080):** MWCC's normal spill choice when g has few uses inside loops. Read loop-invariant indices into
  locals before loops that make calls (`n = g->nring; g->ring[n].c[j] = ...`, not `g->ring[g->nring].c[j]`), and use
  `s32 arg0` with a cast local, which puts the slot low (a `Scene *g` parameter spills high, after the locals)
  (b475:01E00080, 66% → 99.9%).
- **An index `(x % 2 << 1) + i`** fixed `addu` operand order where `x % 2 * 2 + i` did not (b475:01E00080).
- **A constant multiply belongs at the use inside the loop** (`k = t / 12.0f; ... + 5.0f * k`), not
  `k = 5.0f * (t / 12.0f)` (b483:01E00080).
- **A second call argument kept in a saved register (grid ripple):** reuse one local for that argument and a later
  value, assigned twice, so it is not folded into its use past the first call (b474:01E00080, 135 → 29 words).
- **Two calls in one expression with local arguments:** MWCC calls first the one whose argument local was computed last.
- **A loop test `j + 1 < 2` right after an inner loop:** the inner loop reuses the outer counter (b767:01E05B60).
- **f20/f21 float locals swapped across sections:** each float name is one web; rename floats per use-site group
  (greedy search) (b261:01E00080).
- **A division issued first that feeds a later statement:** compute it into an earlier, otherwise dead float local
  first (`r = t / 16.0f; s = ...; f = -25.0f + 80.0f * r;`) (b261:01E00080).
- **Spawn header `on = 1; t = 0;` with the 1 and the slot index in swapped registers (writing `t = 0` first fixes the
  registers but swaps the stores):** compute the address before the constant through a two-use pointer from a
  constant-offset base: `base = g->wave; w = &base[n]; w->on = 1; w->t = 0;` (plain `w = &g->wave[n]` emits
  `addu g, off`). Doesn't work when the array's offset is 0x8000 or more (b475:01E00080; b261 open).
- **A wave sprite loop with float constants loaded early and the loop init late:** set the counter before the
  per-wave float, `q = 0; h = 50.0f * (t / 64.0f); for (; q < 64; q++)` (b639; b474 29 → 21 words).
- **A degrees-to-radians value scheduled among the stores before sin/cos:** write it inside each call argument and let
  CSE share it (b558:01E04830).
- **A 16-byte stack vector overlapping two u8[4] locals stored at direct sp offsets:** the past-the-end form
  (`Vec4f p[2]; u8 c0[4]; u8 c1[4];` using `p[2]`) matches where a union leaves 13 words (b629:01E04E70).
- **In-file side-by-side diff of one function:** `work/sd1.sh <func>` after `tools/mod_infile.sh`.
- **A float constant in the wrong FPR on a value computed once before a loop:** put the multiply in the loop's own
  expression (`... - 30.0f * (f32)j` with `j = max - life;` before the loop) and let it be hoisted (b762:01E05260).
- **A field read early into a saved FPR across a sin/cos call when the angle is a named local:** write the angle inline
  in each call argument (b021:01E04320).
- **The wrong stack-vector field kept in a saved register:** write the value into the stack field and the scene field
  as one chain, `g->pos[j].x = p[3].x = expr;` (b458:01E05250).
- **-O1 parameter-copy moves in the wrong order at entry:** copy the second parameter into a declared local too
  (`s32 code = arg1;` after the cast `g`) (b605:01E059B0).
- **A spilled int local 4 bytes low:** `__attribute__((aligned(8)))` on the local (b706:01E055E0).
- **A sub-expression computed before an `if` with its sum after it:** a local used at least twice (once-used locals
  fold back) (b617:01E003A0).
- **Loop-invariant hoisting stops one level early:** assign the invariant inside the loop (`ang = 270.0f + 3.5f * age;`
  then `sin(PI * ang / 180)`) so the next product is not hoisted (b617:01E003A0).
- **Inner-loop index rebuilt from `i` every outer pass:** index `a[j * 10 + i]` directly (b706:01E055E0).
  Declaration-move search: work/declmove_ft.py.
- **A two-level setup loop with the counter and the reused index swapped:** sweep every permutation of the names
  (outer, inner, index) over just that block with fulltry; greedy one-loop renaming missed it (b062:01E05BB0).
- **Grid-quad loop with the `k+1` index and colour-copy pointers swapped (`$a0`/`$a1`):** add the scroll offset into one
  texture coordinate where it is assigned (`u0 = (f32)(k % 16) / 16.0f + w;`), keep it at the other's uses (`u1 + w`),
  write `u1` as one expression, and `(void)alpha;` after the first alpha byte (b253:01E00080, 23 → 0).
- **Spawn header with `slot = g->t % K`, K a power of two:** `n = g->t; n %= K;` fixes the swapped registers and the
  early constant 1; for K = 24 (a divide) it does not (the b261/b643 wall).
- **A float-constant load one slot early before `func_00187B48(&v, &v, K)`:** cast the first argument,
  `func_00187B48((void *)&v, &v, 1.4f);` (b643:01E00080).
- **Burst sprite loop with colour bytes stored before the fptoui and hoisted floats rotated:** the multiply inside each
  branch, `alpha = (u32)(128.0f * a); (void)alpha;`, `spr.c.q = 1.0f;` in both arms; own float names for that section
  (b175:01E00080).
- **An integer alpha scheduled after the colour stores:** assign it to a local before the first colour byte (b175).
- **The line-strip packet (regs 0x414141) has an 8-byte tail** (b175:01E00080).
- **Spawn header `g->arr[n].on = 1; g->arr[n].t = 0;` with the constant 1 and the slot index swapped (and the b475
  pointer form unusable because the array is past 0x8000):** `n = <index>; (void)n;` then the plain indexed stores in
  on-then-t order. Works for `n = g->nburst` and `n = g->t % 24` (b204, b048, b261, b643:01E00080); this closes the
  b261/b643 "wall" noted above.
- **Loop-counter spill slots:** counters spilled per loop get high slots grouped by name, in reverse loop order within
  a name; a variable whose first loop is spilled gets a low slot below `g`. Rename whole loops so each name's first use
  matches the original (b290, b507, b175:01E00080).
- **A seven-value equality chain on t (`beq ...; b`):** a `switch` with ascending cases (the chain runs descending)
  (b599:01E00080).
- **A shared named angle temp in a grid/ring loop can flip registers far away** (g and `code` swapped at entry): write
  the angle inline or give it a name used nowhere else (b371:01E00080, b571).
- **When single-loop renames stall because fixing one loop breaks another:** a random search renaming 1–4 loops at a
  time, accepting equal scores (work/srch_rnd.py), then revert renames one by one to keep only the needed ones
  (work/srch_minim.py) (b371:01E00080).
- **Grid-quad ST values:** `s0 = (f32)(k % 2) / 2.0f; s1 = (f32)(k % 2 + 1) / 2.0f + h;` with s0's add at its uses
  (b246, b371:01E00080).
- **A scale computed early into a saved FPR before a call:** `s = ...; (void)s;` (b768:01E00080).
- Per-range rename search: work/srch_fgrp.py / srch_grnd.py (check that a picked name isn't live across the range).
- **Init clear loops:** the first loop using a counter name gets counter v1 / pointer a0, later loops with that name
  a0/v1; when only the first clear loop is v1/a0, every init loop uses the same name (then re-search the main path)
  (b141:01E00080).
- **An `addu` with operands in the wrong registers in a call argument:** try `(i << 16) / 8` for `(i << 16 >> 3)`
  (b562:01E00080). Scripts: work/srch_rnd_ft.py, srch_minim_ft.py, srch_angform.py, sdops.py.
- **Which saved FPR a float gets:** names also used in the setup branch get the higher saved FPRs; reuse the setup's
  names for values in f24/f25 (b399:01E00080). Grid-quad offsets `t0 + w` at the uses put the hoisted sums low.
- **Pinning computation order:** give the part its own local followed by `(void)x;` (`h = 600.0f * j / 32.0f; (void)h;`)
  (b399:01E00080).
- **Float STs in a sprite packet with `.s` through the kept `&spr.uv0` register but `.t` direct:** uv0/uv1 as a union
  of the bitfields and `{f32 s, t}` (b399:01E00080).
- **Keep `jp[i * 2 + 1]` an index with an `sll` at each use:** `n = i * 2;` inside the loop, index `jp[n + 1]`
  (b296:01E00080). Fast parallel scorers: work/fastscore.py, vfast.py, declperm_fast.py, srch_*_fast.py.
- **Frame 8–0x18 bytes too small with an unexplained gap between packets:** the gap is a packet's tail (`Spr.tail` as
  `u8[0x20]`, or a `u64 tail` on a Quad) (b454, b295:01E00080).
- **A call argument moved into `$a1` too early:** cast a different argument of that call (`(void *)&g->scr`) to set the
  evaluation order (b022:01E00080).
- **`x += 0.0f` with no other load:** `x += 0.0f * g->obj` (MWCC drops `0.0f * y` but keeps the add); a bare `+= 0.0f`
  disappears (b022:01E00080). Donor pickers: work/adiff.py, work/calldiff.py.
- **A kept ST address in a spill slot (frame 0x20 too big):** uv0/uv1 as a union of Uv and St, written
  `spr.uv0.st.s/t` directly (b563:01E00080).
- **`r = K * (sum)` with the product in the constant's register:** `r = sum; r = K * r;` (b014, b209:01E00080).
- **Donor picker by callee or constant:** `python3 work/famfeat.py <callee or constant>...`; cast search: work/castsrch.py.
- **Spill-slot groups by loop name:** the name used first in the function gets the lower block; read the original's
  slot map and choose names so the right group comes first (b271, b587:01E00080). Exhaustive name assignment over the
  clear loops plus the first main-path loops: work/loopcombo_ft.py (`--groups=` for nested loops).
- **A constant-zero offset hoisted into a saved FPR:** write it in the family's `K + K2 * t / N` form with both
  constants 0.0f; a bare `h = 0.0f` is propagated (b271:01E00080).
- **Saved registers rotated by one across many later sections:** usually one loop-counter rename somewhere; the random
  search (srch_rnd_ft) finds it where greedy and loopcombo miss (b392, b724:01E00080).
- **A once-used angle temp spilled high:** assign it to a name already used earlier in a register (b392:01E00080).
- **An invariant `i % 2` kept unscaled in a spill slot:** `q = i % 2;` inside the innermost loop (b214:01E00080).
- **A one-slot spawn array keeping the field address in a saved register:** `n = g->t; n %= 1;` with `g->beam[n]`
  (b392:01E00080). A `func_00208D00` argument loaded by nothing visible is the 1 left in `$a0` by a `== 1` test (b724).
- **A constant ring radius the original hoists into a saved FPR before a sin/cos loop:** `r = 45.0f + 0.0f * g->t2;`
  before the loop (the zero product folds late, so the constant stays hoisted); `r = 0.0f;` inside a loop keeps an
  `mtc1 $zero; mul.s` (b212:01E00080). `(a * 0x10000) / 20` fixed an `addu` order `(a << 16) / 20` did not.
- **Alpha multiply operands swapped in a product of two calls:** write it inline,
  `alpha = (u32)(128.0f * f(t, 3.0f) * (1.0f - f(t, life)))` (b188:01E00080).
- **Constant ± corner pairs with long loads:** `r = 1.4f; s = 0.7f;` with `-r`/`-s` (b188:01E00080). Relative ranker:
  work/callrank.py.
- **A variable spilled low where the original's sits in the high name-grouped block:** the original first uses that
  name as a setup clear-loop counter (b592:01E00080). Slot map tool: work/slotmap.py.
- **Three colour bytes stored together after three fptoui calls:** u8 locals each followed by `(void)c;` (b151).
- **An `x * 1.0f` the original keeps:** load the 1.0 into a float local first (b151:01E00080).
- **Constant GPRs taken in the wrong order before a loop:** write the constant multiply inside the loop
  (`h = t / 64.0f;` before, `50.0f * h` at the use) and let it be hoisted (b022, b470, b519:01E00080).
- **A setup clear-loop counter coloured first that loop renames can't fix:** merge the main-path variable sharing that
  name into another int local with a disjoint live range, then rename the clear loop (b592:01E00080).
- **The second of two u8 alphas spilled high where yours spills low:** both are one variable reused (b291:01E00080).
- **A zero kept in a saved register and stored as a colour byte:** an `s32` local assigned 0 (b766:01E00080).
- **After a single-function module matches, check fulltry for words in a later function of the module** (b766's new
  24.0f moved func_01E02B40's constant order; fixed with a block local in the same commit).
- **A loop's counter, buffer and kept addresses rotated with no counter rename fixing it:** rename the plain int temps
  of that section (work/fswap_fast.py) (b182:01E00080).
- **A screen-space frame 0x20 bigger than the locals with no references in the gap:** `Vec4f out[4]` with only out[0]
  and out[1] used (b182:01E00080).
- **Every saved register shifted by one:** score structure first with work/opsscore.sh (opcode-only differences),
  then the random loop-rename search fixes the shift (b754:01E00080, 250 → 0 words).
- **One int field loaded as `lwc1`+`cvt` and as `lw`:** compute the int part into a local first, then the float part
  inline (b754:01E00080).
- **The context pointer in `$fp` where a first `Scene *g = (Scene *)arg0;` puts it in `$s0`:** declare the cast local
  last (b249:01E00080).
- **A `[n + 1]` / `[n + 2]` group recomputed as `base + 3l*16` where yours strength-reduces:** `n = l * 3;` inside the
  loop and index with `n` (b249, 70% → 94%). Opcode-only scoring: work/vfastops.py, work/opsdiff.py.
- **Frame 0x10 too small with spilled int temps above the counter group:** spill groups follow each name's first use
  in the whole function; rename the temps to a name the setup already uses (b217:01E00080).
- **Two loop counters in each other's spill slots:** a name used in only one loop keeps its own low slot in declaration
  order; a name used elsewhere spills to the shared high block. Give one loop a unique, correctly placed name and
  rename the other to a name whose first loop isn't spilled (b739:01E00080).
- **Pillar quad with the `k % 4` temp in the wrong GPR and the half-width scheduled early:** `a = 30.0f * f;` right
  before the corner block and `x = k % 4; e = (32.0f * x) / 128.0f;` right before the ST stores (b705:01E00080).
- **For modules whose function is first in the file, the standalone fastscore equals the in-file score**, so the
  parallel `*_fast` searches are reliable on the 01E00080 family.
- **A switch whose default sets the result, laid out as a beq chain with the default in the first delay slot:**
  `n = -1;` before the switch, no default (b612:01E00080).
- **Spawn loops copying the joint vector straight from g even inside `for (i < 1)`:** the source copies a fixed
  element (`p[i] = g->jp[0]`) (b030, b441:01E00080). Segment compare at each jal: work/jalseg.py.
- **A setup clear loop stuck at counter v1 / pointer a0 when every rename disturbs other loops:** give its counter name
  an earlier web from a plain statement before the loop, e.g. `i = func_001F5560(...); g->jn = i;` or
  `j = 0; g->on3 = j;`; later loops with that name then get a0/v1. Keep the statement after the name's original first
  use so the spill groups stay (b054, b624, b623:01E00080).
- **An address kept in a saved register in the original, recomputed in yours, with your register holding a hoisted
  `&x[k]`:** the inner loop indexes that array too: `Vec4f pos[6][1]`, `pos[k][l]` (b066:01E00080).
- **`x / 2.0f` ST pairs with numerator and constant FPRs swapped:** divide into two locals, then add in separate
  statements (`p = n / 2.0f; q = (n + 1) / 2.0f; s0 = p + f; s1 = q + f;`) (b222:01E00080).
- **Warm level can matter in this family too:** b009:01E00080 is level 1 (config/mod_warm.txt).
- **`jp[n + 1]`'s address computed before `jp[n]` in a call:** the index in its own local, `j = n + 1;` (b466:01E00080).
- **callrank can miss the best donor:** compare candidates with work/opadiff.py (register-masked asm diff) (b744).
- **Constants in swapped `$v0`/`$v1`, one `lui` too early, the constant used by stores and a later float argument:**
  compute the product using the other constant into a local before the stores (`b = 15.0f * r;`) (b358:01E00080).
- **High spill block order is by each name's first use, latest first:** give a temp a name first used after the variable
  below it and also used elsewhere; lower a counter with `j = 0; g->on = j;` in setup (b358:01E00080). Twin comparison:
  work/twindiff.py.
- **Grid-quad ST registers swapped (`u1`/`w1` in `$f3`/`$f5`):** declare the floats `u0, w1, w0, u1`; a second quad block
  gets its own four locals (b511:01E00080).
- **An outer loop's branch target on `func_0020EB40`:** the matrix setup is inside the loop (b372:01E00080).
- **A loop-counter name used only once in the main path takes a low spill slot and shifts the frame by 0x10:** rename it
  to a name used elsewhere (b554:01E00080).
- **A late loop counter spilled below the alpha slots where the original has it above:** reuse `buf` as that counter
  (b442:01E00080). Which matched function covers each stretch of a target: work/covermap.py.
- **A colour-address temp one register low (`$a1` for your `$a2`) with no fptoui nearby:** test warm level 1 before
  searching C variants (b006:01E00080).
- **`mul.s $f22, $f22, $f0` coming out constant-first:** `s *= 0.8f;` (b012:01E00080).
- **Consecutive high spill slots following loop order in reverse are one counter name** (b420:01E00080).
- **`lq`/`sq` matrix copy from a stack `f32[4][4]`:** copy through a struct declared `aligned(16)`, `m4 = *(Mq *)m3;`
  (b420:01E00080).
- **Preheader order counter, pointer, second induction variable:** an explicit `i = 0` lands before the hoisted pointer;
  write the second value from the counter (`K + i * M`) or walk an explicit pointer set between them (b131, c516).
- **A walking pointer starting one element before an array:** the preceding same-type field and the array are one table
  (c516:01E03130).
- **A draw-loop preheader scheduled wrong:** set the counter right after the per-slot value,
  `f = ...; j = 0; p = ...; for (; j < N; j++)` (c401:01E00080).
- **Keeping `(i + 1) * 64` as its own induction variable:** `y = i * 64 + 64` (b456:01E00080). `t * 0x8000 / life` fixed
  registers `t << 15` left swapped. Masked diff of a draft: work/mdiff.py.
- **A discarded `func_0020B480` call followed by `add.s` with a zero register:** `r = 0.0f * func_0020B480(x) + A;`; the
  product folds but the call and add stay (b216:01E00080).
- **A `bne` whose delay slot copies the first instruction after the `if`:** that code is outside the `if` (b216).
- **The low spill block is ordered by each name's first use, latest first** (frame 0x10 short with int temps between
  `n` and the byte alpha: move the alpha's first use after the temp's) (b738:01E00080). Statement-order hill climb under
  def/use constraints: work/stmtperm.py.
- **A setup block that looks like a preheader may be inside the loop:** check the back-branch target before hoisting it
  (b156:01E00080).
- **Saved FPRs rotated across a big function:** srch_frnd_fast.py with one group per section and variable plus spare
  float names (b625, b156:01E00080).
- **A setup-grid counter coloured before the strength-reduced temps:** reuse a variable dead in the setup branch (`ot`)
  as the outer counter; if spill slots shift, give the old counter name an early use inside the loop (b575, b249:01E00080).
- **A step count spilled above the temps where the original has it below:** it is no variable; write `32 - y` inline at
  each use (b249:01E00080).
- **Unexplained scheduling around packet fields:** read fields directly, not through `*(u16 *)(s32)&` casts (b575).
- **A whole-function register swap (`ot`/`code`):** delete each statement in turn and watch which registers the two get;
  it pointed at one `if` whose call arguments belonged in int locals (b471:01E00080, 86 → 20).
- **A constant loaded in the wrong order with the multiply already in place:** `r = K * s; (void)r;` at the top of the
  loop (b212:01E00080). `e = A; e = e * B / K;` for a result in the wrong saved FPR (b100:01E00080).
- **An ST pair with `q = l % N` and the `q + 1` conversion scheduled early:** drop `q`:
  `z0 = 0.5f * (l % N) / N.0f; z1 = 0.5f * (l % N + 1) / N.0f;` before the stores (b722, b738:01E00080).
- **`1.0f + 1.5f * (1.0f - f)` computed among the colour copies:** assign it in the innermost loop before its first use
  so it hoists (b722, b738, b647:01E00080).
- **Saved registers rotated around a loop bound or counter:** a fresh local used nowhere else (b647, 58 → 11).
- **An int field wanted as `lw` + `mtc1` where you get `lwc1`:** read it into an int local first (b846:01E00080).
- **`lw` / `dsll32` / `dsra32` around `func_001A0660`:** a real s64 divide (`__divdi3`): `q = x; *p = q /= K; *p = -q;`
  with `s64 q` (b112:01E04480).
- **A `% 2^n` index with the field load first after the join:** `n = i % 32; (void)n;` and index with `n` throughout; an
  index kept across a call likewise (b541:01E00080, 166 → 28).
- **A field read reusing an earlier value where the original reloads it:** a one-element array read through a zero index
  local (`n4 = 0; g->beam[n4].t`) (b846:01E00080).
- **A register fixed only by renaming a distant setup loop:** the name needs an earlier web; replace the rename with
  `g->x = n = 0;` (b456:01E00080).
- **An extra saved FPR with the frame 0x10 short and many later hunks:** a value hoisted out of an inner loop; put it in
  a local before the loop (b723:01E00080, one statement, about 1000 instructions).
- **Spilled "counters" in the low walker block that step by a constant:** strength-reduced `j * K`, not variables (b373).
- **High or low spill slot depends on the name's first web:** first web spilled = low slot; an earlier unspilled web sends
  it to the high block. Move it with `g->x = j = 0;` placed by the first-use order you need (b543:01E00C30).
- **`sb $zero` to a spill slot, then `lbu` and a store of that byte:** a fade with strength 0, `(0x30 - t) * 0 / 48`; a
  plain `alpha = 0` is propagated (b543:01E00C30).
- **A kept address lost to another kept address:** delete each top-level section and watch the frame and kept
  `addiu sN, sp`; a one-iteration loop the original lacks can add the extra webs (b373:01E00080).
- **Check immediates before chasing registers:** compare non-stack immediates on the opcode-aligned diff (b373).
- **One `addiu a0` out of place next to float arguments:** `floatsearch.py --calls <callee>`; a prototyped alias plus
  float locals on both calls (b001:01E044C0).
- **A delay slot swapped with a store before a `jal`:** `(void *)` casts on the address arguments, in combinations; in
  b474:01E00080 only the 2nd and 3rd together worked.
- **A byte temp and a counter in each other's spill slots:** give the byte its own u8 name covering one earlier unspilled
  web and reuse a counter name with earlier webs (b717:01E00080).
- **Re-tune float calls in order after fixing one**, scoring only the words up to each call's `jal`, with backtracking
  (b037:01E04FB0, 273 tries).

## Stale words after a function's padding (config/mod_pieces.txt)

The tell: the C matches every instruction up to the function's `jr $ra`, but the asm file goes on past the zero
padding with a loop tail and an epilogue for another frame size, which branches back into the function (an older,
longer build's leftovers). The splitter files it with the function because of that backward branch. The fix is
not C: add `<module> <VADDR of the first stale word>` to `config/mod_pieces.txt`, add
`INCLUDE_ASM(..., func_<VADDR>_<module>)` after the function in the module's C file, and run `make` (it re-splits
the module; the linker script PROVIDEs the labels the piece branches to). Closed b153:01E00080, b506:01E02460,
c022:01E01850 and b058:01E023F0 (b058 also wanted mode 0 as `if/else` instead of an early `return`: the early
return dropped the `nop` between the loop's `bnel` and the epilogue).

## The permuter on module drafts (tools/perm, 24 November 2026)

`tools/perm/perm.sh FUNC DRAFT MINUTES JOBS` runs decomp-permuter on a module draft and re-checks every output it
writes. Plain `dk perm` gets three things wrong there, so its "best" versions were mostly worse, and older "permuter
tried" notes may never have searched the real code:

- **Other bodies.** The permuter turns every other function into a prototype, but MWCC uses the body of a static
  callee defined earlier, even one it calls with `jal`. Without it, c560's base came out about 300 instructions off.
  `strip.py` keeps FUNC's callees (transitively) and makes the rest prototypes; `run.py` is the toolchain permuter
  with `extract_fn` patched to keep those bodies. (Marking them `inline` instead inlines them all: 1410 instructions.)
- **Pragmas.** The permuter's C printer moves `#pragma` lines onto the wrong declarations. `strip.py` puts the
  pragmas in force at FUNC at the top of the file and drops the rest.
- **Score.** The permuter's score is not the instruction count (a register difference costs less than a moved
  load), and a lower score can be a worse count. `perm.sh` keeps every output better than the base, not just the
  best score, and `check.py` counts each one exactly.

It also needs a GNU `cpp` on PATH (or at `work/cppbin/cpp`), and sets TMPDIR so the dependency files of each
compile stay off `/tmp`. What it found: c560 (a temp for the shifted byte and one for the colour word, match after
2 hours), b150 (a vertex pointer, one instruction). A tempting output can add code the original lacks (b046's
`cvt.s.w`, b193's second store): read `tools/perm/diff.py` before applying one.
