# Yu-Gi-Oh! The Duelists of the Roses: matching decompilation

A matching decompilation of **Yu-Gi-Oh! The Duelists of the Roses** (PlayStation 2, NTSC-U, `SLUS_205.15`):
C source that compiles to the exact bytes of the retail executable and of the game's 762 code modules.

This repository contains no game data. You need your own copy of the game to build anything.

## Status (30 October 2026)

| | Functions in C | Code in C |
|---|---|---|
| Main executable (`SLUS_205.15`) | 3,463 of 3,463 (100.0%) | 100.0% of 1.5 MB |
| Code modules (`DATA/BMODULE.MRG`, `CMODULE.MRG`, `MMODULE.MRG`) | 7,137 of 8,620 (82.8%) | 57.6% of 11.6 MB |

- `make check` rebuilds the whole executable and all 762 module files and compares them byte for byte with the
  originals. A function counts as done only when its C is in that build and the check passes.
- The target is the retail US release: `SLUS_205.15` sha256
  `1df7759b68e6aee73d8deab2efd2e556ec553d952af00fe8bf0f499a57298719`, the same executable as the dotr-decomp
  project. The code modules are the retail disc's `DATA/BMODULE.MRG`, `CMODULE.MRG` and `MMODULE.MRG`.
- No main-program function is kept as assembly on purpose any more: the vector-unit functions are C with a
  small inline-assembly block for the VU0 instructions. About 110 others, mostly Sony's system-call stubs and a few vector-unit
  helpers, are written as assembly inside the C files and do count.
- 87 of the main-program functions came from the dotr-decomp project's CC0 bundle (another team decompiling
  the same game).
- Module functions repeat across modules; one C file per distinct function is renamed into every module that has
  a copy.

## Compilers

- Game code and modules: Metrowerks CodeWarrior for PS2 2.3.3 (`mwccps2`, build 000906),
  `-O4,p -sdatathreshold 0 -relax_pointers`; some module functions use `-O1,p`, `-O2,p` or `-O3,p`, set per
  function with `#pragma optimization_level`. Some files only match when the compiler has compiled another file
  first in the same process ("warm"); `config/warm_files.txt` lists them.
- Sony's libraries: ee-gcc 2.9-991111. The C library (newlib 1.9.0): ee-gcc 2.96. All GCC files are preprocessed
  with the 2.96 preprocessor; `tools/cc.sh` reproduces the old assembler's behaviour.

None of the compilers are included.

## Building

1. Put your `SLUS_205.15` (sha1 `bee9fc13d12ab2818822d905d820320fc6427f23`) in `assets/`, and give the path
   of your own disc image (the modules are read from it) in `dk.local.json` (ignored by git):
   `{"disc": "/path/to/your.iso"}`, or in the `DK_DISC` environment variable.
2. `make split`, `make split-modules`, then `make check`.

The scripts currently assume our local toolchain layout (`~/decomp/toolchain`, see `config.mk` and `tools/cc.sh`),
set up by [decomp-kit](https://github.com/kira-502/decomp-kit), which also reads the disc image; expect to adapt a
few paths.

## Contributing with an AI agent

The code modules are the open work: 2,005 functions are still assembly. [AGENTS.md](AGENTS.md) is a complete guide
for an AI coding agent (setup from zero, the work loop for one function, the rules that bite, how to send work back);
[docs/TODO-MODULES.md](docs/TODO-MODULES.md) lists what is left, smallest first, with the hard ones marked, and
[docs/MATCHING-TIPS.md](docs/MATCHING-TIPS.md) collects the tricks that made functions match. Human contributors:
the same files, plus [CONTRIBUTING.md](CONTRIBUTING.md) for names and fixes.

## PC port

[DotR-PC](https://github.com/kira-502/dotr-pc) is a native Windows port built from this C: its generator turns
the decompilation into C for 32-bit Windows, and the 762 code modules are translated from MIPS. Like this
repository it holds no game data: bring your own disc. Its README and BUILDING.md say how to build it;
[decomp-kit](https://github.com/kira-502/decomp-kit) sets up the toolchain this repository builds with.

Neither project is affiliated with or endorsed by Konami.

## Layout

- `src/<area>/<system>.c`: the main executable, one file per system in a folder per area (`src/duel`, `src/ai`,
  `src/render`, ...); `docs/CODE-MAP.md` says which file holds what, and the next section how the files are cut.
- `src/mod/<module>.c`: the code modules; functions not yet in C are included as assembly.
- `include/functions.h`: prototypes of every main-program function.
- `config/`: splat configuration, linker names, the module list.
- `tools/`: compile wrapper, jump-table fixer, module split/pack/check, post-build patch step.

## How the files are split

The US executable has no symbols, so the project first cut the code by address (`main_000.c` .. `main_080.c` and
a file per very large function). The files are now cut by system, at Konami's own file boundaries wherever the
evidence shows them, one folder per area (`docs/CODE-MAP.md` is the map):

- **The evidence.** The Japanese release (`SLPM_650.50`) kept its symbol table, including each source file's local
  symbols: the string pool (`@stringBase0`), numbered literals (`@NNN`), statics (`name$NNN`) and static
  functions. A function that uses a local symbol of the function before it was in the same original file;
  Metrowerks numbers literals upwards within a file, so a function that starts again at a lower number, or a
  second string pool, starts a new one. Our functions are matched to the Japanese ones by name.
- **Names.** A file is named for what it holds (`ai/weevil.c`, `render/rhgeom.c`). Where the table gives no
  boundary, the developers' function prefix (`SzView_`, `RhGeom_`, `Taku_`) decides.
- **Large files in parts.** Two original files are cut into parts by feature: the duel screen (one file of 361
  functions, `duel/szduel_*.c`, 12 parts) and the effect helpers (`effect_lib/`, 4 parts). Each file's first line
  says which part it is.
- **The computer AI.** Every computer duelist's AI is its own original file, named after the duelist its
  controller in `duelistControllers` serves; Joey's file also holds the controller of duelist 16 (Shadi).
- **Sony's libraries** and the C library (`src/sdk/`) keep their address cuts, renamed: see `src/sdk/README.md`.
- **Rules of the build.** A file is one address range and the files link in address order (the data is one
  block, so only code moves). Where two old files declared the same global with different C types, the later
  file names it `<name>_2`, a linker alias (`config/linker_syms.txt`).
- **Compiler state.** Metrowerks carries memory from one function to the next inside a file: some functions match
  only behind the functions that were compiled before them in the old cut. So six files start where they do for
  the compiler, not at a feature boundary: `duel/szduel_act.c` (for `SzDuel_Act`), `duel/szduel_cards.c`
  (`SzDuel_SetupCard_Pipe`), `battle/szbattle.c` (`lSzBattle_DrawGrass_Pipe` and `lSzBattle_DrawFakeShadow`;
  it opens with the duel screen's last three functions), `game/szview_look.c` (`SzView_RollCamera`),
  `campaign/taku_camp_cinema.c` (`Taku_Camp_TEXT_WHO`) and `campaign/taku_camp_act.c`
  (`Taku_Camp_ENEMY_WINDOW`, which matches only first in its file). Each says so in its first line.

## Names

The Japanese release (`SLPM_650.50`) shipped with its symbol table. 3,087 main-program functions carry their
real names from it (for example `SzDuel_Act`, `SzEffect_GetRef2`), matched to this executable by code (199 of
them by their position between code matches). The old address names (`func_001F5620`) still work as aliases
(`config/old_names.txt`); the code modules still use them. The module functions keep their address names for
now.

The same symbol table names 1,020 data objects; 255 of the main program's globals carry those names so far,
with their old `D_` names kept as aliases (`config/old_data_names.txt`). Globals are being given English names
that say what they are (the duel state `gSzDuel_dl` is now `duelState`, described by `DuelState` and
`DuelPlayer` in `include/game.h`); the JP name stays as a note and an alias. How names are chosen:
`docs/NAMING.md`. Every function of the main program carries a one-line comment; guides for modders (the code
map, how a duel runs, where the data and the save live) are in `docs/README.md`, and how to propose a change is
in `CONTRIBUTING.md`.

**batzpup's names.** batzpup's Ghidra project of this game (his export of 18 October 2026) names functions, data,
structs and enums too, and many of those names are used here. Each computer duelist's AI functions carry the
duelist's name (`TaLogic_Weevil_GetMinimumTask`; a developers' name that was already unique, such as
`TaLogic002_GetNearUnit`, stays). Where his reading of a function says more than ours and the code agrees, his name
is the function's name (`SzGame_DEBUGMENU`, `Ta_Eff_001_Revive`), the developers' name kept as an alias and a note.
Globals our code still called by address (`D_0029008A`) carry his labels (`AttributeIconID`), 110 of
them. His structs for a unit, a board square and the computer opponent's tasks (`Unit`, `MapInfo`, `UnitTask`,
`MinimumTask`, the first part of `DuelPlayer`, which he calls `LogicData`) are in `include/game.h`, the unit's
layout checked against the developers' own debug information, and his enumerations (terrain, attributes,
duelists, map places, cut scenes, card ids, ...) in `include/enums.h`. Every other name of his is a linker alias (`config/ghidra_names.txt`), so the names his project uses link and show
in `build/main.map`. Names, structs and enums from batzpup's Ghidra project, used with his permission.
Thanks to batzpup.

## Credits

- Blayr: module matching.

## License

Our own work in this repository is released under **CC0 1.0** (see `LICENSE`). Code taken from other projects
keeps its original license and credit: see `THIRD_PARTY_NOTICES.md` (kfiv-decomp, the ICO decompilation,
gt4-decomp, newlib 1.9.0).

Yu-Gi-Oh! and The Duelists of the Roses belong to their respective owners. This project is not affiliated with
or endorsed by them.
