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
  multi-loop variables the one mentioned first gets the lower register. Declaration order does nothing
  (b594:01E02EC0, b494:01E013C0, b281:01E02440). When the count is itself a setup counter, put the step and draw loops
  on the setup's other counter and zero that first (`a = 0; m = 0; k = 0;`) (b215:01E02E50). Repro in work/wall2/.
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
