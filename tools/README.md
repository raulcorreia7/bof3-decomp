# Tools

Every routine task is one command from the repository root. `<image>` is a target id with `/` written
as `+`. Run each Python tool with `.venv/bin/python tools/<name>.py` or directly (`tools/<name>.py`);
`--help` prints its verbs and examples. The Meson names run as `meson compile -C build/meson <name>`.

## Tasks

| Task                                     | Command                                                                  | More                                                      |
| ---------------------------------------- | ------------------------------------------------------------------------ | --------------------------------------------------------- |
| Set up                                   | `tools/setup.sh --dev` (`--matching`, `--no-payloads`, `--no-sdk`)       | [toolchain: setup](../docs/toolchain.md#setup)            |
| Check the disc, extracted files, images  | `tools/disc.py verify`                                                   | [toolchain: disc](../docs/toolchain.md#disc-manifest)     |
| Build and check every image              | `meson compile -C build/meson check`                                     | [toolchain: commands](../docs/toolchain.md#commands)      |
| Check one image                          | `meson compile -C build/meson check-<image>`                             | same                                                      |
| Rank the open functions, cheapest route first | `tools/worklist.py -n 10 [--image <name>]`                          | `--help`                                                  |
| Write rows for another program           | `<tool> --jsonl` (worklist, dups, sigs, quality `--queue`, symbol refs, template_diff, m2c_sweep) | `--help`                                                  |
| Run every check before a push            | `meson compile -C build/meson pre-push`                                  | [pre-push](#pre-push)                                     |
| Compare one function with retail         | `tools/match.sh <target>@0x<ADDR>`                                       | [match.sh](../docs/toolchain.md#matchsh)                  |
| Preprocess the context for m2c or a scratch | `tools/m2ctx.py include/common.h -o ctx.c`                            | [m2c](../docs/toolchain.md#m2c)                           |
| Draft and upload                         | m2c draft, then a decomp.me scratch with the project flags               | [m2c](../docs/toolchain.md#m2c), [decomp.me](../docs/toolchain.md#decompme) |
| Permute a near match                     | `tools/permuter_import.py src/<path>/<Name>.c`                           | [permuter](../docs/toolchain.md#permuter)                 |
| Find a template for an assembly function | `tools/template_diff.py <target>@<func>`                                 | [template diff](#templates)                               |
| Try the closest template for one function | `tools/template_try.py <target>@<func>`                                 | [template diff](#templates)                               |
| Try templates in batch                   | `tools/template_try.py rows.jsonl`                                       | same                                                      |
| Try one C body for an assembly function  | `tools/try_body.py <target>@<func> body.c`                               | [try body](#try-body)                                     |
| Draft open functions with m2c, keep exact | `tools/m2c_sweep.py --sample 200`, `tools/m2c_sweep.py --image <image>` | [m2c sweep](#m2c-sweep)                                   |
| Write the seed bundle of one function    | `tools/seed.py <target>@<func>`                                          | [m2c sweep](#m2c-sweep)                                   |
| Measure shapes, write bodies for them | `tools/gen_body.py shapes`, `tools/gen_body.py call-seq`                  | [body generators](#body-generators)                       |
| Find twins in one image                  | `bin/coddog match <target> <func> -t 0.95`                               | [coddog](../docs/toolchain.md#coddog)                     |
| Find alike functions across images       | `tools/dups.py near`                                                     | [duplicates](#duplicates-and-names)                       |
| List same-name groups and split names    | `tools/dups.py shared-names`, `tools/dups.py split-names`                | same                                                      |
| Find repeated instruction runs in functions | `tools/chunks.py -w 24 -o chunks.jsonl`                               | [duplicates](#duplicates-and-names)                       |
| Mark each run asm, shared or pasted      | `tools/classify.py chunks.jsonl out.jsonl`                               | same                                                      |
| Find repeated C bodies in the source     | `ripwire src --clones`                                                   | same                                                      |
| Rename a function or global everywhere   | `tools/symbol.py rename OLD NEW` (an address name: `--image <target> --local`) | [rename steps](../docs/naming.md#rename-steps)       |
| Rename parameters                        | `tools/symbol.py params <func> old=new ...`                              | same                                                      |
| Rank units to name first                 | `tools/symbol.py refs src/<path>`                                        | same                                                      |
| Find the symbol and member at an address | `tools/symbol.py at <target> 0x<ADDR>`                                   | [lookup](#lookup)                                         |
| Find the member at a record offset       | `tools/symbol.py member <Type> 0x<OFF>`                                  | same                                                      |
| List every reference to a symbol         | `tools/symbol.py uses <Name>` or `tools/symbol.py uses <target>@0x<ADDR>` | same                                                      |
| Find the name of a bare number           | `tools/symbol.py value 0x<NN> [--image <target>] [--type <EnumOrPrefix>]` | same                                                      |
| Build the call-graph layers              | `tools/symbol.py layers [--jsonl]`                                       | [lookup](#lookup)                                         |
| Prove a signature from the bytes         | `tools/symbol.py signatures [FUNC\|--all] [--jsonl]`                      | [lookup](#lookup)                                         |
| Find a global's real extent              | `tools/symbol.py extents [<target>] [--jsonl]`                            | same                                                      |
| Read a function's system from the graph  | `tools/symbol.py homes [--jsonl]`                                        | same                                                      |
| Find where a record or global is accessed | `tools/symbol.py accesses <TypeOrGlobal> [--jsonl]`                     | [lookup](#lookup)                                         |
| Rank records by unknown accesses         | `tools/symbol.py records [--jsonl]`                                      | same                                                      |
| Scan matched bodies for bare values      | `tools/symbol.py values --scan [--jsonl]`                                | [values](../docs/conventions.md#how-a-value-is-written)   |
| Add a symbol row                         | `tools/symbol.py add <target> <Name> 0x<ADDR> --source "<description>"`     | [symbols](../docs/layout.md#symbols-and-the-link)    |
| Check the symbol table                   | `tools/symbol.py check`                                                  | [symbols](../docs/layout.md#symbols-and-the-link)    |
| Split a data unit                        | add a `[0xOFFSET, type, name]` row to `config/<target>/splat.yaml`       | [split](../docs/toolchain.md#split)                       |
| Count readability debt, gate touched files | `tools/quality.py`, `--queue`, `--diff BASE`, `--markdown [--update]`                         | [quality](#quality)                                       |
| Check type loss between two revisions    | `tools/typeloss.py HEAD~5 HEAD`                                          | `--help`                                                  |
| Scan prototypes against definitions      | `tools/sigs.py scan`                                                     | `--help`                                                  |
| Format                                   | `meson compile -C build/meson format` (or `tools/format.sh`)             | [toolchain: commands](../docs/toolchain.md#commands)      |
| Write the progress report                | `meson compile -C build/meson report`                                    | [toolchain: commands](../docs/toolchain.md#commands)      |
| Set up a worktree for parallel work      | `tools/worktree.sh --from <checkout> [--dir <dir>] <branch>`             | [worktrees](#worktrees)                                   |
| Read bytes through Rizin                 | `bin/rz <target> 'pdf @ <func>'`                                         | [rizin](../docs/toolchain.md#rizin)                       |

## Templates

A template is a matched C function with the same shape as an assembly function. `template_diff.py`
lists the closest by opcode sequence and prints only the instructions that differ: `~` same opcode,
other operands; `-` only in the template; `+` only in the target.

```sh
tools/template_diff.py emi/plchar/plp016/00@func_801CF610
tools/template_diff.py <target>@<func> <template target>@<template func>
```

`template_try.py` takes one function ref, `tools/template_try.py <target>@<func>`, and tries its
closest template; or rows of `TARGET@NAME<TAB>TEMPLATE@NAME` (`dups.py near --full --jsonl` writes
them as objects with the keys `target` and `template`, cheapest first). It lines up the template's
instructions with the target's. Where only a
relocation symbol differs, it names the target's symbol in the template's C; where only an
immediate differs and that literal (or the numeric macro that holds it) occurs once, it writes the
target's value. It declares what the body now uses in the image header, then calls `try_body.py`.
Each row prints `EXACT`, `REMAP-EXACT` (after a rename or literal), `FAIL` with the number of
differing instructions and the first difference, or `SKIP`. A kept body is a lead: run
`check-<image>`, then name it from evidence and share it
([shared bodies](../.agents/skills/decomp/references/refactor.md#shared-bodies)). Both tools read the function index
`build/func_index.json.gz`, built from the images on first use; add `--rebuild` after a build.
They need `rapidfuzz` for the search (`tools/setup.sh --matching`).

### Try body

`try_body.py` puts a C body in place of one `INCLUDE_ASM(<func>);` line, runs `tools/match.sh`, and
keeps every edit only on `match`; any other result restores each touched file.

```sh
tools/try_body.py <target>@<func> body.c        # or `-` for stdin
tools/try_body.py --batch rows.tsv              # rows: <target>@<func> <TAB> body.c
```

A line `@decl <declaration>` in the body file (an `extern`, a prototype or a `#define`) is removed from
the body and added to the image header, the first include of the C file, unless an include of that
file already declares the name. Output: `EXACT`, `FAIL` with the first difference, or `SKIP`.

## m2c sweep

`tools/m2c_sweep.py` drafts open functions with m2c, runs each draft through `tools/try_body.py` and keeps the exact ones, writing `build/m2c_sweep/results.jsonl` (target, status, differing, variant) and, with `--jsonl`, one object per printed line; `tools/seed.py <target>@<func>` writes the same drafts, the twins, callers and callees into `work/<image>/<ADDR>/` for one function. Both give m2c a typed work cell: the context declares `g_SpadView`, a pointer to the mode's work record (the type the unit casts `g_Task` to, else the image family's record), and the assembly reads `0x1F800044` through it, so drafts name members instead of `->unkN`. The draft spells the cell `g_Task`, or `((T *)g_Task)` where the unit defines no view macro. A context without a complete record keeps the raw cell. The `--help` text lists the options.

## Body generators

`gen_body.py` lifts the assembly of a branch-free function into calls and stores and writes C from
it with the repo's names (`config/symbols.toml` by address, `g_Task` members by offset).
`shapes` counts every `INCLUDE_ASM` function by shape (`call-seq`, `store-seq`, `spad`, `dispatch`,
`straight`, `branch`); `tools/gen_body.py <shape> [rows.tsv] [--dry-run]` writes a body per member
(`MATCH`, one statement per call or store), declares missing globals in the image header and keeps
the body only when `tools/match.sh` reports an exact result. Twins with one body at one address
share `<func>.h`; twins at several addresses print `TWIN` and stay for a naming pass. A
body is a lead: run `check-<image>`, then name it from evidence.

The tool names a work-cell member through the nested structs and unions of the record (`header.step`,
`pos.x.fixed`) and a word inside a record such as `g_Game` as its member. It writes no branch, `jalr`
or load through an argument pointer, so a function with one prints `SKIP` and its first unlifted
instruction. `worklist.py` lists a function on the `generator` route only when the tool can write its
body; a `SKIP` function moves on to the template or plain route.

## Duplicates and names

`dups.py near` groups functions with alike opcodes across all images and names the matched template of
each assembly function; `near --full` writes one row per assembly function with its cheapest template
and `diff_count`, the instructions that differ (jump targets ignored), cheapest first. `shared-names`
lists one name that several bodies use, worst first. `split-names` lists byte-equal bodies that carry
several names. All print tab-separated rows, or one JSON object per line with `--jsonl`.
`chunks.py` finds instruction runs (immediates masked) that recur in three or more functions and
writes JSON Lines with each group's `members`; `classify.py` reads and writes that form and
marks each member asm, shared (a header body or a call) or pasted, so the rows left are the copies to
fold. `ripwire src --clones` lists token-normalized duplicate C bodies.

## Lookup

`symbol.py at` prints the named owner of each address in one image: `NAME+0xOFF (type, size) [table]`,
the member path when the owner is a record (`g_Game.members[2].pos.x`), or `no named owner`. It reads
the image's table and the resident ones; `--diff [BASE]` reads the `D_` addresses the branch adds.
`symbol.py member` prints the member path and type at a record offset from clang's own layout, and
`symbol.py uses` lists the C uses, the open functions' assembly uses and the Rizin cross-references in
one table; the first query in an image analyses its Rizin project and caches the references under
`build/symbol-xrefs`. `symbol.py value` lists every enum member and numeric macro with one value
among the headers the image sees, nearest scope first, so a bare `0x3A` becomes `ABILITY_SANCTUARY`.
`symbol.py layers` builds the game call graph over every image, including table dispatch, and prints
each function's layer, callers, callees, status, copies and shared flag. `--jsonl` writes one object
per line. `symbol.py accesses` decodes every image and reports a record's or global's byte offsets,
widths, members, examples, constants and call slots with their width, signedness and straddle
problems; `symbol.py records` ranks every record by accesses times unknown members.
`symbol.py values --scan` decides what each numeric literal of a matched body means from the
declaration it is assigned to or compared with, and prints the family, the existing constant and the
form the conventions prescribe; `--jsonl` writes one object per site.
`symbol.py signatures` reads every split function and interprets its register dataflow as the
signature GCC 2.7.2 would compile from it: the argument registers read before they are written, the
stack arguments, each argument's kind and record, and the returned value or void, cross-checked
against the argument registers and the returned `v0` of every caller. Each row carries the declared
prototype, the found signature and a confidence. `symbol.py extents` gives each data and bss symbol
its distance to the next symbol, the size its declaration states, the accesses past that size, its
index stride and the neighbours only reached as `base + constant` from it. `symbol.py homes` reads
the call and data graph: the systems of each function's callers, callees and data, the systems that
read and write each global, and the address runs of each source file. `--jsonl` writes one object per
line for each of the three.

## Quality

`quality.py` counts, per directory and in total: matched functions still named `func_<ADDR>`, `D_` and
`unk_` tokens, raw width casts, harmful fake helpers, `FAKE:` notes, bodies pasted into several images
under one name (`pasted`, one `Name.h` is the rule) and under several names (`twins`). `--queue` lists
files worst first. `--diff BASE` compares BASE with `--to` (default `HEAD`) and exits 1 when `casts`,
`harmful` or `pasted` rose over the files the change touched (a moved body nets to zero), when a function
present before and after holds more `D_`/`unk_` tokens (`names`), or when a body named before is now `func_<ADDR>`
(`addr`); a new `MATCH` body is exempt from both. `BASE` is compared at its merge-base with `--to`. `--gate` picks
other metrics. `--queue --jsonl` writes the same rows as objects. A commit message line `Quality-Allowed: <path> <metric>` accepts one rise in one file. Old debt in an untouched file never fails. `report` stores the totals under `quality` in `report.json`.

## Pre-push

`pre_push.sh [BASE_REF]` (Meson target `pre-push`) runs the 15 checks below, one line each, and keeps
the logs in `build/pre-push/`. CI runs it too. `BASE_REF` defaults to the newest of `public/main`,
`origin/main` and `main`.

| Check           | Fails when                                                                              | Needs      |
| --------------- | --------------------------------------------------------------------------------------- | ---------- |
| `check`         | an image differs from its retail SHA-1                                                  | disc       |
| `check-headers` | a public header does not compile alone                                                  | compiler   |
| `check-plain`   | a source does not build as plain C                                                      | compiler   |
| `check-tree`    | an added line has a register pin, decompiler local, stack name, task offset, m2c macro, raw address, duplicate prototype, wrong header guard or shared body; a tracked file is game data or over 1 MiB, a relative include or import, or an enum member | none |
| `externs`       | a `.c` file gains an `extern` line                                                      | none       |
| `include-asm`   | there are more `INCLUDE_ASM` lines than at the base ref, in total or in one image       | none       |
| `format-check`  | C, Python, TOML or Markdown differs from the formatter                                  | the tools  |
| `meson test`    | a tool test fails                                                                       | Python     |
| `typeloss`      | a rename, move or retype weakens a type                                                 | none       |
| `markers`       | a definition in `src/` lacks exactly one status marker, or a change adds a `NON_MATCHING` draft | none |
| `names`         | a new name carries an 8-digit address, a listed legacy one is gone, or an added line names a parameter `argN` | none |
| `addrs`         | a symbol address that `config/symbols.toml` records on `main` is gone                   | none       |
| `kept`          | a named helper, define, global, type, member or function is lost or degraded            | none       |
| `quality`       | a touched file gains casts, fake helpers, `func_`/`D_` names or pasted bodies           | none       |
| `subsystems`    | never fails; writes the debt table to `build/subsystems.md`                             | none       |

`check-plain` skips a source whose plain preprocessed text compiled before: the keys are empty files
under `~/.cache/bof3-cc/plain`, shared like the object cache, so a header change recompiles only the
sources that include it. `BOF3_CC_CACHE=0` turns that off, and `HEAVY_JOBS` caps its jobs.

## Worktrees

`tools/worktree.sh --from <checkout> [--dir <dir>] <branch>` adds a Git worktree under
`.worktrees/<branch>` (or `--dir <dir>`) and links the local inputs, toolchains, `.venv` and
extracted disc from a built checkout, so the new worktree builds without extracting again. Keep
that checkout while the worktree exists.

## Build plumbing

Meson, setup or another tool calls these. A contributor does not run them.

| File                                         | Job                                                                     |
| -------------------------------------------- | ----------------------------------------------------------------------- |
| `setup.py`, `setup.sh`, `psyq.sh`, `psyq_lib.py`, `fetch_verified.sh` | Install the toolchain and extract the disc                |
| `split.py`, `link_symbols.py`                | Split an image and write its link script                                |
| `cc.py`, `psxdecomp/dmpsx.py`                | The compiler wrapper (it caches objects in `~/.cache/bof3-cc`; `BOF3_CC_CACHE=0` turns that off) and the DMPSX rewrite |
| `objdiff_config.py`, `rzproject.py`          | Build the objdiff project and the Rizin projects                        |
| `check_addrs.py`, `check_kept.py`, `check_markers.py`, `check_names.py`, `check_asm.sh`, `check_externs.sh`, `check_configured.sh`, `check_plain.sh`, `check_tree.sh`, `check_enum_members.py` | The bodies of the `addrs`, `kept`, `markers`, `names`, `include-asm`, `externs`, `check-headers`, `check-plain` and `check-tree` gates |
| `format.sh`                                  | The body of `format` and `format-check`                                 |

`decomp_yaml.py` writes coddog's manifest and is called by `bin/coddog`, not by the build.
`bin/coddog` finds twins and `bin/rz` reads retail bytes; no other tool does either. `bin/internal/` holds `find-tool` and the binutils wrappers (`as`, `ld`, `nm`, `objcopy`, `objdump`) that the build uses.

## Layout

One flat file per task: `tools/<name>.py`, in snake case, with verbs as sub-commands. Shared logic
lives in the `tools/bof3/` package, and the tests are in `tools/tests/`. A command with no arguments
that every contributor runs is also a Meson run target.
