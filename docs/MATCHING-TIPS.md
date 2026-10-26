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
- **Spreading a `-O1`/`-O2`/`-O3` shape:** `tools/mod_spread.py` copies the typedefs and the definition but not the
  `#pragma optimization_level` lines around it, so its copies of such a shape do not match; carry the pragmas over
  to each copy. (Fixed 26 Oct: the tool now carries the pragma lines, their resets and the comments above the
  function.)
- **Accepts carry your own name:** `dk accept` commits with your `git config user.name` / `user.email` (set both in
  the repository; it stops if either is missing).
