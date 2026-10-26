# AGENTS.md: working on this decompilation with an AI coding agent

Read this whole file before you change anything. It is written for an agent that knows nothing about the project.

## What this is

A **matching decompilation** of *Yu-Gi-Oh! The Duelists of the Roses* (PlayStation 2, NTSC-U, `SLUS_205.15`): C
source that compiles to the exact bytes of the retail game.

- The main executable is done: 3,463 of 3,463 functions are C.
- The game also loads **762 code modules** from `DATA/BMODULE.MRG`, `CMODULE.MRG` and `MMODULE.MRG` (card effects,
  battle animations, scene scripts). They hold 8,620 functions; about 6,600 are C, the rest are still assembly.
- **The open goal: every module function in C that compiles to the original bytes.** The list of what is left is
  `docs/TODO-MODULES.md`; the tricks that worked so far are `docs/MATCHING-TIPS.md`.

Rules that never bend:

1. **Matching only.** A function is done when its C compiles to the original bytes and `make check` passes. Close
   is not done.
2. **Honest C.** Code a programmer could have written. Allowed: per-function `#pragma`s, block-scope `extern`s and
   prototypes, a no-prototype `extern void f();`, `(void)x;` after an assignment, `do { } while (0)`. Not allowed:
   padding functions, inline asm for ordinary code, hand-patched words, build steps that strip or rewrite output.
3. **No game data in the repository, ever.** No disc images, executables, `.mrg`/`.mwo` files, extracted assets,
   textures, sound, video. `.gitignore` keeps `assets/`, `build/`, `asm/`, `work/` and `dk.local.json` out; keep it
   that way.
4. **Do not reformat or rename code you are not matching.** Other files' bytes depend on them (see "Things that
   bite").

## Setup from zero (Linux or WSL2 Ubuntu 24.04)

You need your own copy of the game (a disc image of the US release).

1. System packages (Ubuntu):
   ```
   sudo apt install build-essential git curl xz-utils python3 python3-venv python3-pip bison flex texinfo
   ```
2. The toolchain and the `dk` tool come from [decomp-kit](https://github.com/kira-502/decomp-kit). It installs
   everything into `~/decomp/toolchain` (about 2 GB): GNU binutils for mipsel, the Metrowerks compilers (run
   through [wibo](https://github.com/decompals/wibo)), the EE GCC builds, splat, m2c, mwccgap, coddog,
   decomp-permuter, asm-differ, objdiff.
   ```
   git clone https://github.com/kira-502/decomp-kit ~/decomp/kit
   bash ~/decomp/kit/setup/toolchain.sh
   ln -sf ~/decomp/kit/dk ~/decomp/toolchain/bin/dk
   . ~/decomp/toolchain/env.sh          # every new shell: puts dk, wibo, coddog, m2c on PATH
   ```
3. **The compiler that matches is Metrowerks CodeWarrior for PS2 2.3.3, build 000906** (`mwcps2-2.3.3-000906`),
   flags `-O4,p -sdatathreshold 0 -relax_pointers` (some functions use `-O1,p`/`-O2,p`/`-O3,p`, set per function,
   see below). 2.4 and every 3.x build do **not** match. The toolchain script downloads it from decomp.me's
   compiler archive; `config.mk` already names it.
4. This repository:
   ```
   git clone https://github.com/kira-502/dotr-decomp ~/decomp/games/dotr
   cd ~/decomp/games/dotr
   ```
   `dk accept` commits as you: set `git config user.name` and `git config user.email` here first (it stops if
   either is missing).
5. The game files, from **your own disc**: copy `SLUS_205.15` from the disc root into `assets/` (sha1
   `bee9fc13d12ab2818822d905d820320fc6427f23`), and tell the build where the disc image is (the modules are read
   from it): create `dk.local.json` (ignored by git) with `{"disc": "/path/to/your.iso"}`, or set `DK_DISC`.
6. Split and build:
   ```
   make split            # the executable's assembly into asm/
   make split-modules    # reads the three .MRG files from your disc, splits the 762 modules into asm/
   make -j4 check
   ```
   Done when the last two lines are:
   ```
   OK: build/SLUS_205.15 matches the original
   OK: 762 modules match the disc
   ```

## Where things are

- `src/mod/<module>.c`: one C file per module (`b000.c` .. `b853.c`, `c000.c` .. `c621.c`, `m000.c`). Functions not
  yet in C appear as `INCLUDE_ASM("asm/nonmatchings/mod/<module>", func_<VADDR>_<module>);`.
- `asm/nonmatchings/mod/<module>/func_<VADDR>_<module>.s`: the original assembly of one function (after
  `make split-modules`). Module data: `asm/data/mod/<module>/`.
- `include/`: `common.h` (types), `functions.h` (main-program prototypes), `game.h`/`structs.h` (shared structs).
- `config/modules.tsv`: the module table; `config/module_names.tsv`: real function names from the Japanese release.
- `docs/TODO-MODULES.md`: what is left (regenerate it: `python3 tools/todo_modules.py`).
- `drafts/mod/<module>_<VADDR>.c`: best earlier drafts of hard functions (not built; starting points).

Names: a module function is `func_<VADDR>_<module>`, e.g. `func_01E029E0_b211` at address `0x01E029E0` in module
`b211`. Its "shape id" in TODO-MODULES.md is `b211:01E029E0`. Modules load at `0x1E00000`, code starts at
`0x1E00080`.

## The work loop for one module function

Pick the next row of `docs/TODO-MODULES.md` (kind `work`, smallest first). Then:

1. **Look.**
   - `cat asm/nonmatchings/mod/<module>/<func>.s`
   - `dk draft <func>`: m2c's first draft, written to `work/<func>.c`.
   - The real name: `grep -P "^<module>\t<VADDR>" config/module_names.tsv`. Functions with the same name in other
     modules are often already C and often the same source: `grep -n "<shape id>\|<name>" src/mod/*.c` (every
     matched shape starts with a `/* shape MOD:VADDR, N insns ... */` comment) and `coddog match <func> -t 0.8`.
     Copying the closest finished one and fixing the differences is usually the fastest way.
   - A `drafts/mod/` file, if the TODO row names one.
2. **Write the C** in `work/<func>.c`, in the house form:
   ```c
   #include "common.h"

   /* shape b211:01E029E0, 86 insns, 4 copies: one line saying what it does */

   typedef struct Obj_b211_01E029E0 {      /* local types carry the shape id as a suffix */
       s32 kind;
       f32 scale;
   } Obj_b211_01E029E0;

   typedef struct Tbl_b211_01E029E0 {
       Vec4f v[4];
   } Tbl_b211_01E029E0;

   static s32 func_01E029E0_b211(Obj_b211_01E029E0 *o, s32 kind) {   /* ALWAYS static */
       extern Tbl_b211_01E029E0 D_01E05080_b211;   /* module data: block-scope extern of its D_ label */
       Tbl_b211_01E029E0 tbl = D_01E05080_b211;    /* a local table is a struct copy of that data */
       extern s32 b211_01E00080();                 /* another function of this module: <module>_<VADDR> */
       ...
   }
   ```
3. **Try it:** `dk try <func> work/<func>.c --lines 80`.
   - `MATCH ...; fits in the game`: go to step 4.
   - `N/M instructions match`: read the diff (original left, yours right) and change the C. The tips file lists
     what each kind of difference usually means.
   - `CLASH`: your file clashes with its module file in the real build (a missing `static`, a typedef name the file
     already has, a global the file declares with another type). See `docs/MATCHING-TIPS.md`, "Clashes".
   - Close, and the only differences are argument registers reloaded around a call to a static function of the same
     module: try it in its real spot, `tools/mod_infile.sh <func> work/<func>.c`, or just go to step 4.
4. **Accept:** `dk accept <func> work/<func>.c`. It puts your C into `src/mod/<module>.c`, rebuilds the module,
   checks every module against the disc and commits. `ACCEPTED` = done; `REJECTED` = the build no longer matches,
   nothing was kept.
5. **Copies:** if the TODO row says the shape has copies in other modules (`also in ...`), spread it:
   `python3 tools/mod_spread.py <func> --consts`. It copies your C to every module with the same shape, renames the
   module's labels, swaps constants that differ, tries each copy and accepts the ones that match in one build.
   It carries the function's `#pragma` lines (an `-O1`/`-O2`/`-O3` twin) and comments with it.
6. Re-run `python3 tools/todo_modules.py` from time to time.

Give one function a serious try (start small, change one thing at a time, keep the best version), then move on.
A function that will not match: add a line to `config/module_notes.tsv` (`shape<TAB>best %<TAB>hard: why`), keep
the draft in `drafts/mod/`, take the next one.

## Things that bite (details and more in docs/MATCHING-TIPS.md)

- **`static`.** Module functions are static. Without it `dk accept` adds a prototype to `include/functions.h` and the
  build fails with "identifier expected" on every line.
- **Tables are module data.** `T tbl[4] = {{-1.0f, ...}}` makes the compiler emit its own copy (`%hi(@34)` in the
  diff where the original has `%hi(D_...)`). Wrap the array in a struct and copy the module's label (above).
- **Flag sets.** Most module code is `-O4,p`. A function whose branch delay slots are all `nop` and whose `addiu sp`
  comes before `jr ra` was built at `-O2,p` (or `-O1,p` when every field is reloaded in each statement); one that
  keeps `x == 5 || x == 6` as two compares is `-O3,p`. Wrap it:
  `#pragma optimization_level 2` before the function, `#pragma optimization_level reset` after it.
- **Order matters across functions.** Metrowerks carries state from one function to the next inside a file: a
  function can compile differently depending on what came before it in the same run. `dk try` compiles your
  function alone first, then in its file; `dk accept` and `make check` build the real file. Trust those.
- **Static callees above you.** When your function calls a static function defined earlier in the same module file,
  the compiler knows which registers it leaves alone and skips reloads. Plain `dk try` cannot see that and shows a
  few extra `move`/`addiu` lines; `tools/mod_infile.sh` and `dk accept` can.
- **Never edit another file's code to make yours match**, unless the asm proves it (for example a sibling that really
  takes an unused extra argument its caller passes). Then the full `make check` must still pass.

## Sending work back

- One pull request per batch of modules (for example "b200-b249: 31 functions"), each function accepted by `dk accept`
  (so each is its own commit), plus spreads.
- `make -j4 check` green on both lines before you push. Paste the two OK lines into the pull request.
- Only `src/mod/*.c` (and, when needed, `config/module_notes.tsv`, `drafts/mod/`, `docs/TODO-MODULES.md`) should
  change. No reformatting, renaming or comment edits elsewhere.
- Commit messages: what you matched, and any trick a later reader needs (`b211: LkSetLight, table as module data`).
- Add a short section to the end of `docs/MATCHING-TIPS.md` when you find a new rule: the tell, the fix, the
  function it closed.
