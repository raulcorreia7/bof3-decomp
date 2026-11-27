# Units

How the source splits into translation units, how the build turns them into the disc, and the plan
that moves every image from one file per function to one file per original object.

## The model

One `.c` file is one object of the retail link: the functions it compiled, in link order, with the
data only those functions use. The retail bytes show where an object ends ([evidence](#evidence));
where they show nothing, the image or engine module is one unit, the smallest grouping that needs no
invented history.

| Item                               | Rule                                                                                                                                                                                                                                     |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| unit file                          | the bodies in address order, after the image or module header include and the unit's own data; one `c` row of the image's `splat.yaml` at its first function                                                                             |
| unit name                          | an image with one unit: `<archive>_<slot>.c`; several units: `<role>.c` in lower snake case for what the unit does (`battle_hooks.c`); an unknown role: the offset name (`6FD0.c`) until the functions are known                         |
| header                             | one per image (`<archive>_<slot>.h`) and one per engine module (`<module>.h`), as [layout](layout.md#lowest-scope-wins) says; a unit has no header of its own                                                                            |
| shared source                      | a body or run of bodies that several images link: one body header under `src/overlays/<group>/shared/` or `src/shared/`, included where it sits in each unit; the unit is the only includer in its image, so no thin wrapper file exists |
| same source, other table           | each image keeps its unit and includes the shared body; the value that differs is a setting in the image header ([shared bodies](../.agents/skills/decomp/references/refactor.md#shared-bodies))                                         |
| `.rodata`                          | compiler-made: jump tables and literals stay inside the unit; the zero fill before the next unit's tables is a row of its own (a one-word data file today)                                                                               |
| `.data`, `.bss`                    | a table only one unit uses is defined in that unit, `static` once no other unit reads it; a table several units read stays in the image's data file with one `extern` in the image header                                                |
| draft (`NON_MATCHING`)             | stays inside its unit with its `#else INCLUDE_ASM`; the split writes one assembly file per function of a `c` row ([missing](#build))                                                                                                     |
| hand assembly (`asm/<image>/hand`) | its own row and object, as in the original link                                                                                                                                                                                          |
| PsyQ member                        | the SDK object itself (`config/sdk/library-units.jsonl`); it bounds the game objects around it                                                                                                                                           |

## Evidence

Measured over all 428 images (12,529 functions). The scripts and per-boundary rows are outside the
repository (`~/.cache/bof3-swarm/tu/`); this table is the rule they found.

| Signal                  | What the bytes show                                                                                                              | Grade      |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------------------- | ---------- |
| `.rodata` start         | each object's `.rodata` starts at an 8-byte offset from the image's rodata run; a zero word fills the gap (119 of 127 fills fit) | proven     |
| a literal pooled twice  | GCC keeps one copy of a string per object, so two copies lie in two objects (`"%d"` in `game/00`)                                | proven     |
| PsyQ member             | the 732 SDK units of `config/sdk/library-units.jsonl`                                                                            | proven     |
| recurrence              | a run of bodies, equal after relocations, whose neighbour differs from image to image                                            | recurrence |
| shared next to own code | a body that three or more images link next to code only one image has                                                            | probable   |
| data runs               | data after `.text` used by disjoint function runs, in address order                                                              | probable   |
| `.text`                 | objects are packed at 4 bytes: 5 nop pads in 12,529 gaps, so code alone shows no boundary                                        | none       |

A proven boundary is an interval: after the last function that uses one object's tables and before
the first that uses the next. A boundary inside an interval of several functions goes before the
first function of the next repeated block, else before the first table user; the unit's
`splat.yaml` row records that choice.

| Family          | Images | Functions | Units (proven + recurrence) | With probable | `c` rows today | `.c` files today |
| --------------- | -----: | --------: | --------------------------: | ------------: | -------------: | ---------------: |
| executable      |      1 |       647 |              147 (139 PsyQ) |           153 |            311 |   engine folders |
| `game/00`, `01` |      2 |       701 |                           5 |            26 |            685 |              269 |
| menu and commu  |     13 |     1,104 |                          34 |            80 |            727 |              803 |
| area            |    203 |     3,748 |                         278 |           504 |          3,116 |            4,011 |
| battle          |      5 |       959 |                           8 |            13 |            966 |              977 |
| bmagic          |    124 |     2,470 |                         184 |           254 |            154 |              154 |
| boss            |     35 |       797 |                          37 |            86 |            382 |              771 |
| plchar          |     19 |       576 |                         143 |           143 |             99 |              121 |
| scenario        |     25 |     1,401 |                          96 |           136 |            230 |              329 |

204 images show no boundary and stay one unit each. In `scenario` 22 fills contradict the function
order, so its boundaries count as probable. 159 runs of 48 words or more recur in two or more images
(417 functions): the menu equipment windows of `bate`, `shisu`, `shop` and `start`; the area HUD
banner; the plchar script runner; the bmagic sparkle effect; `Trail_*` in area and scenario. The
world04 images `area176` to `area184` hold identical code, as do `area160`, `163` and `164`; boss,
bmagic, scenario and area pairs that differ only in a table are the same source built twice.

What the bytes never show: a boundary between two objects whose `.rodata` already ends on an 8-byte
offset or that have none, the file names, the order of `static` functions inside a file beyond
link order, and whether a shared run was one object linked into each overlay or a file included into
each.

## Build

The studio's pipeline, as the disc records it, and the target that runs each step here.

| Step                                                              | Here                                                                              | State                                                                                        |
| ----------------------------------------------------------------- | --------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
| compile each unit (GCC 2.7.2, ASPSX, `-O2 -G0`)                   | `tools/cc.py`, one Ninja edge per `c` row                                         | exists                                                                                       |
| link the executable with PsyQ 3.7                                 | `exe+slus_004_22` with the SDK member objects                                     | exists                                                                                       |
| link each overlay at its window, against the executable's symbols | one image per target; `tools/link_symbols.py` provides the executable's addresses | exists                                                                                       |
| write the PS-X EXE and the raw overlay payloads                   | `build/meson/<image>.bin`                                                         | exists                                                                                       |
| pack each EMI from code and assets                                | `tools/disc.py rebuild` runs `bof3 emi pack` per archive                          | exists; assets are the extracted retail entries                                              |
| master the disc                                                   | `bof3 assets import disc` patches a copy of the retail image                      | partial: system area, directories, Form 2 streams and track 2 come from the retail image     |
| one assembly file per function of a multi-function `c` row        | `tools/split.py`                                                                  | missing: today the split names the assembly for the row, so a draft cannot sit inside a unit |
| a `c` row named by its path from `src/` (`engine/sound/sound`)    | `tools/split.py`, `tools/bof3/resolve/`                                           | missing: the engine images use 758 `../` rows                                                |

The ISO volume (`BREATH_OF_FIRE3`, preparer `CAPCOM CO.,LTD.`) was mastered on 1998-03-26. Every
archive that holds code has that date, and the data-only archives keep older ones (BENEMY
1997-06-16, BGM 1997-07-07, BPLCHAR 1997-10-30, the XA streams 1996-1997): the release run relinked
every program and repacked the archives that carry code, and copied the asset archives as built
before. The EMI packer leaves fixed fill (`0x2E` after the table of contents, `0x5F` after each
payload) and no stamp; files lie in directory order, which is the order of the executable's disc
file table.

## Disc round trip

```sh
tools/setup.sh --dev                    # extract the disc into build/disc (once)
BOF3_CC_CACHE=0 meson compile -C build/meson disc
```

`disc` builds every image from C, packs all 880 EMI archives from the built images and the extracted
entries, writes them and both executables into a copy of the disc in `build/disc-rebuild/disc/`,
seals every sector it writes (EDC and parity), and compares the SHA-1 of each whole track and the cue
sheet with `config/disc.toml`, then every extracted file. It prints both hashes of each track. In a
worktree without its own `build/rust`, set `BOF3_CLI` to the `bof3` binary.

Result on `main`: track 1 `5745d9dde965ed0ec673ba071deb762355fa3e1a` and track 2
`d9f92af296360772e62caa4cb276de3fa74f5538`, equal to the Redump image. The rebuilt files cover about
two thirds of track 1; the rest (the 25 system sectors, the directories, the four STR and XA streams,
the 150 lead-out sectors) and track 2 are copied from the retail image. A disc mastered from nothing
needs an ISO writer that lays files in directory order with the retail dates, the licence sectors,
the Form 2 streams and the stray parity of LBA 188323; that is not built.

## Splat rows

A `c` row names a unit, never a function. A unit's tables are one `.rodata` row at their first
address, its fill a row of its own. An image's rows shrink from one per function to one per unit (6,676 `c`
rows to about 1,000 to 1,400). Until the split writes one assembly file per function, a unit with a
draft keeps three rows: the matched part before it, the draft's own file, the part after it.

## Matched state

`MATCH` markers stay on each function, so a merge moves markers and never adds or drops one.
`tools/check_matches.py` compares MATCH functions per image by address, so a move between files
passes; `tools/check_markers.py` checks each definition; `report.json` counts functions from the
symbols of each image, not files. A unit PR changes no address, no marker and no byte.

## Rules and checks the migration changes

| Place                                                                | Today                                                                                          | After                                                         |
| -------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| [layout: files](layout.md#files)                                     | one function per file is the default; a `.c` file claims no original source                    | one unit per evidenced object; this page holds the evidence   |
| [layout: translation units](layout.md#translation-units-of-an-image) | the unit file includes the function files                                                      | the unit file holds the bodies                                |
| [layout: engine modules](layout.md#engine-modules)                   | designed modules; `INCLUDE_ASM` stays out of a unit                                            | module units at proven edges, drafts inside                   |
| [matching](matching.md#a-function-in-a-file-with-other-functions)    | split a unit to place a jump table                                                             | the unit's `.rodata` row holds every table                    |
| `.agents/workflow.re.yml`                                            | `at_match`: keep the function in its file; `at_100`: module units; a naming lane moves no file | units are written before matching ends; a rename edits no row |
| match brief, Never list                                              | no `splat.yaml` edit                                                                           | unit rows change only in a unit PR                            |
| `tools/check_sources.py`, `check-tree`                               | count rows and wrappers                                                                        | unchanged: bodies in a unit are named sources                 |
| `tools/quality.py`                                                   | sums metrics over touched files                                                                | unchanged: a moved body nets to zero                          |
| `tools/check_kept.py`, `order_check.py`                              | by name; functions in address order per file                                                   | unchanged                                                     |

## Migration

Each PR converts whole images: `git mv` the first function file to the unit name, append the other
bodies in address order, delete the thin wrappers and the merged files, replace the rows. The proof is
`BOF3_CC_CACHE=0` `check-<image>` for every touched image, `tools/check_markers.py`,
`tools/check_matches.py public/main` and the full `pre-push`; no `Match-Removed`, `Kept-Removed` or
`Quality-Allowed` line.

| Order | Images                                                                              | Today (files)              | After (about) |
| ----- | ----------------------------------------------------------------------------------- | -------------------------- | ------------- |
| 1     | boss (35, no draft)                                                                 | 771                        | 120           |
| 2     | scenario without drafts (19), `batl_end`, `batl_ovr`                                | 300                        | 130           |
| 3     | area without drafts (177), 30 images per PR                                         | 3,500                      | 900           |
| 4     | the split change: one assembly file per function of a row                           | tools                      | -             |
| 5     | images with drafts: area (26), menu (13), battle (2), bmagic (10)                   | 1,800                      | 500           |
| 6     | `game/00`, then the executable, one engine module per PR, after the row-path change | 269 and the engine folders | 160           |

Files counted include data files and headers. bmagic and plchar already hold one or a few units
per image.

## Contributor path

After the migration a function lives in the unit of its image: `rg -n 'func_801F2C40|Name' src`
finds it, or the image folder's `splat.yaml` row whose offset precedes it. The tree keeps its depth:

```text
src/engine/<system>/<module>.c, <module>.h     the executable and game/00, one unit per module
src/overlays/<group>/<archive>/<slot>/          one image: <archive>_<slot>.h, its units, its data file
src/overlays/<group>/shared/<name>.h            a body or run several images of one group link
src/shared/<name>.h                             a body several groups link
```

What goes: 1,050 thin wrapper files, about 5,500 per-function `c` rows, the 758 `../` rows, and
about 5,000 one-function files. What stays: one header per image and per module, the 494 shared
body headers (fewer, as a recurring run becomes one header).

From clone to a matching build today, with the manual or slow steps:

| Step                                                        | Cost                                                                                         |
| ----------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
| `git clone` the workspace, `make init-game`                 | quick                                                                                        |
| install the host tools `make doctor` lists                  | manual: 13 tools, `clang-format` 23.1.5 and `dprint` 0.64.3 pinned                           |
| put the CUE and two BIN tracks in `decomp/inputs/external/` | manual                                                                                       |
| `tools/setup.sh --dev`                                      | slow: downloads the compiler, binutils and PsyQ, builds `bof3` with Cargo, extracts the disc |
| `meson setup build/meson`                                   | slow: splits 428 images at configure time                                                    |
| `meson compile -C build/meson check`                        | the build                                                                                    |

Removals that shorten it: the per-function rows (the configure split writes one row per unit), the
thin wrappers, and the `BOF3_CLI` export in a worktree (`tools/disc.py` can find the `bof3` of the
checkout the worktree links to).

## Port seams

Where the game touches the PlayStation today, counted over `src/` (calls by name for PsyQ, tokens
for the rest):

| Family                    | PsyQ calls (libgpu, libgte, libapi, libcd, libsnd, libspu, libetc, libcard, libc) | GTE macros | scratchpad and task cell | primitives and OT | address literals |
| ------------------------- | --------------------------------------------------------------------------------- | ---------: | -----------------------: | ----------------: | ---------------: |
| engine                    | 121, 88, 47, 40, 77, 8, 16, 3, 11                                                 |         44 |                    3,352 |               266 |              231 |
| area                      | 681, 606, 1, 0, 0, 0, 0, 0, 91                                                    |          9 |                    6,633 |             1,343 |               97 |
| bmagic                    | 756, 2,099, 0, 1, 0, 0, 0, 0, 150                                                 |          6 |                   14,392 |             1,800 |                2 |
| scenario                  | 212, 232, 0, 0, 6, 4, 0, 0, 50                                                    |          0 |                    2,339 |               388 |               12 |
| battle                    | 84, 9, 0, 0, 1, 0, 0, 0, 47                                                       |          0 |                      779 |               124 |              191 |
| menu                      | 92, 20, 29, 0, 10, 0, 1, 4, 38                                                    |          0 |                       51 |               149 |               27 |
| boss, plchar, commu, logo | small                                                                             |          0 |                    1,257 |               185 |               39 |

Overlays call libgpu and libgte directly and never the CD, SPU or pad: those sit behind the engine
modules (`cd`, `sound`, `input/pad`, `emi/loader`). So the seams are the PsyQ headers in
`include/psyq/` (a port supplies the same functions), the scratchpad cell `g_Self` in
`include/psx/mem.h` (a port makes it a variable), the EMI loader and the fixed overlay windows (a
port links every overlay into one program, so same-address `func_<ADDR>` names in different images
must become `static` or carry the image), and the format headers with their 188 `ASSERT_SIZE` lines
(little-endian, natural packing; records loaded from the disc that hold RAM addresses need a
translation step). Choices that make a port harder: open-coding an SDK macro where the macro matches,
copying engine code into an overlay unit instead of calling it, retail addresses in C, and a global
where the unit evidence allows `static`.
