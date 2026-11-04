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
| Rank the open functions, cheapest route first | `tools/worklist.py -n 10 [--image <name>]`                          | [worklist](#worklist)                                     |
| Run every check before a push            | `meson compile -C build/meson pre-push`                                  | [pre-push](#pre-push)                                     |
| Compare one function with retail         | `tools/match.sh <target>@0x<ADDR>`                                       | [match.sh](../docs/toolchain.md#matchsh)                  |
| Preprocess the context for m2c or a scratch | `tools/m2ctx.py include/common.h -o ctx.c`                            | [m2c](../docs/toolchain.md#m2c)                           |
| Draft and upload                         | m2c draft, then a decomp.me scratch with the project flags               | [m2c](../docs/toolchain.md#m2c), [decomp.me](../docs/decomp-me.md) |
| Permute a near match                     | `tools/permuter_import.py src/<path>/<Name>.c`                           | [permuter](../docs/toolchain.md#permuter)                 |
| Find a template for an assembly function | `tools/template_diff.py <target>@<func>`                                 | [template diff](#templates)                               |
| Try templates in batch                   | `tools/template_try.py rows.tsv`                                         | [template diff](#templates)                               |
| Try one C body for an assembly function  | `tools/try_body.py <target>@<func> body.c`                               | [try body](#try-body)                                     |
| Draft open functions with m2c, keep exact | `tools/m2c_sweep.py --sample 200`, `tools/m2c_sweep.py --image <image>` | [m2c sweep](#m2c-sweep)                                   |
| Write the seed bundle of one function    | `tools/seed.py <target>@<func>`                                          | [m2c sweep](#m2c-sweep)                                   |
| Measure shapes, write bodies for them | `tools/gen_body.py shapes`, `tools/gen_body.py call-seq`                  | [body generators](#body-generators)                       |
| Find twins in one image                  | `bin/coddog match <target> <func> -t 0.95`                               | [coddog](../docs/toolchain.md#coddog)                     |
| Find alike functions across images       | `tools/dups.py near`                                                     | [duplicates](#duplicates-and-names)                       |
| List same-name groups and split names    | `tools/dups.py shared-names`, `tools/dups.py split-names`                | same                                                      |
| Rename a function or global everywhere   | `tools/symbol.py rename OLD NEW --image <target> --local`                | [rename steps](../docs/conventions.md#rename-steps)       |
| Rename parameters                        | `tools/symbol.py params <func> old=new ...`                              | same                                                      |
| Rank units to name first                 | `tools/symbol.py refs src/<path>`                                        | same                                                      |
| Add a symbol row                         | `tools/symbol.py add <target> <Name> 0x<ADDR> --source "<evidence>"`     | [symbols](../docs/conventions.md#symbols-and-the-link)    |
| Split a data unit                        | add a `[0xOFFSET, type, name]` row to `config/<target>/splat.yaml`       | [split](../docs/toolchain.md#split)                       |
| Count readability debt, gate touched files | `tools/quality.py`, `--queue`, `--diff BASE`                           | [quality](#quality)                                       |
| Check type loss between two revisions    | `tools/typeloss.py HEAD~5 HEAD`                                          | [type loss](#type-loss)                                   |
| Scan prototypes against definitions      | `tools/sigs.py scan`                                                     | [signatures](#signatures)                                 |
| Scan arrays for text and struct shapes   | `tools/shapes.py text`, `tools/shapes.py strided`, `tools/shapes.py types` | [data shapes](#data-shapes)                             |
| Write decimal for quantities             | `tools/values.py fields`                                                 | [values](#values)                                         |
| Format                                   | `meson compile -C build/meson format` (or `tools/format.sh`)             | [toolchain: commands](../docs/toolchain.md#commands)      |
| Write the progress report                | `meson compile -C build/meson report`                                    | [toolchain: commands](../docs/toolchain.md#commands)      |
| Set up a worktree for parallel work      | `tools/worktree.sh --from <checkout> <branch>`                           | [worktrees](#worktrees)                                   |
| Read bytes through Rizin                 | `bin/rz <target> 'pdf @ <func>'`                                         | [rizin](../docs/toolchain.md#rizin)                       |

## Templates

A template is a matched C function with the same shape as an assembly function. `template_diff.py`
lists the closest by opcode sequence and prints only the instructions that differ: `~` same opcode,
other operands; `-` only in the template; `+` only in the target.

```sh
tools/template_diff.py emi/plchar/plp016/00@func_801CF610
tools/template_diff.py <target>@<func> <template target>@<template func>
```

`template_try.py` takes rows of `TARGET@NAME<TAB>TEMPLATE@NAME` (`dups.py near --full` writes them,
cheapest first). It lines up the template's instructions with the target's. Where only a
relocation symbol differs, it names the target's symbol in the template's C; where only an
immediate differs and that literal (or the numeric macro that holds it) occurs once, it writes the
target's value. It declares what the body now uses in the image header, then calls `try_body.py`.
Each row prints `EXACT`, `REMAP-EXACT` (after a rename or literal), `FAIL` with the number of
differing instructions and the first difference, or `SKIP`. A kept body is a lead: run
`check-<image>`, then name it from evidence and share it
([shared bodies](../docs/conventions.md#shared-bodies)). Both tools read the function index
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

## Body generators

`gen_body.py` lifts the assembly of a branch-free function into calls and stores and writes C from
it with the repo's names (`config/symbols.toml` by address, `g_SpadWork` members by offset).
`shapes` counts every `INCLUDE_ASM` function by shape (`call-seq`, `store-seq`, `spad`, `dispatch`,
`straight`, `branch`); `tools/gen_body.py <shape> [rows.tsv] [--dry-run]` writes a body per member
(`MATCH`, one statement per call or store), declares missing globals in the image header and keeps
the body only when `tools/match.sh` reports an exact result. Twins with one body at one address
share `<func>.h`; twins at several addresses print `TWIN` and stay for a naming pass. A
body is a lead: run `check-<image>`, then name it from evidence.

## Duplicates and names

`dups.py near` groups functions with alike opcodes across all images and names the matched template of
each assembly function; `near --full` writes one row per assembly function with its cheapest template
and `diff_count`, the instructions that differ (jump targets ignored), cheapest first. `shared-names`
lists one name that several bodies use, worst first. `split-names` lists byte-equal bodies that carry
several names. All print tab-separated rows.

## Signatures

`sigs.py scan` prints one row per prototype that disagrees with its definition, implicit
declaration, call-through cast or return cast (`--kind` selects one). `cross` and `sync` find and
rewrite a prototype that differs from a definition in another file. `uncast` removes the call cast of
one function. Every edit is a lead: run `check` afterwards.

## Type loss

`typeloss.py OLD NEW` lists prototypes and externs that carry fewer named types in `NEW` than in `OLD`
(`WORK` is the working tree). Run it before a pull request that renames, moves or retypes.

## Quality

`quality.py` counts, per directory and in total: matched functions still named `func_<ADDR>`, `D_` and
`unk_` tokens, raw width casts, harmful fake helpers, `FAKE:` notes, bodies pasted into several images
under one name (`pasted`, one `Name.h` is the rule) and under several names (`twins`). `--queue` lists
files worst first. `--diff BASE` compares BASE with `--to` (default `HEAD`) and exits 1 when `casts`,
`harmful` or `pasted` rose over the files the change touched (a moved body nets to zero); `--gate` picks other metrics. Old debt in an
untouched file never fails. `report` stores the totals under `quality` in `report.json`.

## Data shapes

`shapes.py text` finds byte arrays written as hex that hold text; `strided` finds arrays read with a
stride or a wider cast; `types` finds one role name declared with several types; `literal` rewrites a
hex initializer as string rows. The reader of the array decides its type.

## Values

`values.py fields` and `values.py compare` list hex literals that are quantities (coordinates,
primitive macro arguments, compares with named variables). `--write` rewrites them after you review
the lines.

## Worklist

`worklist.py` prints one row per `INCLUDE_ASM` function with its cheapest route: `template0` (a
template with no differing instruction, for `template_try.py`), `generator` (a `gen_body.py`
shape), `template` (up to three differing instructions, for `template_diff.py`) or `plain`. It
reuses `gen_body.py` and `dups.py near --full`, sorts untried functions before those with a hint
above their `INCLUDE_ASM`, and shows that hint. `--route`, `--image`, `-n` and `--tsv` select and
format the rows. It reads the function index, so build first.

## Pre-push

`pre_push.sh [BASE_REF]` (Meson target `pre-push`) runs `check` (with a disc), `check-headers`,
`check-tree`, `include-asm`, `format-check`, `meson test`, `typeloss` and `quality`, prints one line each and
keeps the logs in `build/pre-push/`. CI runs it too.

## Worktrees

`tools/worktree.sh --from <checkout> <branch>` adds a Git worktree under `.worktrees/<branch>` and
links the local inputs, toolchains, `.venv` and extracted disc from a built checkout, so the new
worktree builds without extracting again. Keep that checkout while the worktree exists.

## Build plumbing

Meson, setup or another tool calls these. A contributor does not run them.

| File                                         | Job                                                                     |
| -------------------------------------------- | ----------------------------------------------------------------------- |
| `setup.py`, `setup.sh`, `psyq.sh`, `psyq_lib.py`, `fetch_verified.sh` | Install the toolchain and extract the disc                |
| `split.py`, `link_symbols.py`, `decomp_yaml.py` | Split an image, write its link script, and write the coddog settings    |
| `cc.py`, `psxdecomp/dmpsx.py`                | The compiler wrapper and the DMPSX rewrite                              |
| `objdiff_config.py`, `rzproject.py`          | Build the objdiff project and the Rizin projects                        |
| `check_asm.sh`, `check_hand.sh`, `check_headers.sh`, `check_tree.sh` | The bodies of the `include-asm`, `check-headers` and `check-tree` gates |
| `format.sh`                                  | The body of `format` and `format-check`                                 |

`bin/coddog` finds twins and `bin/rz` reads retail bytes; no other tool does either. `bin/internal/` holds `find-tool` and the binutils wrappers (`as`, `ld`, `nm`, `objcopy`, `objdump`) that the build uses.

## Layout

One flat file per task: `tools/<name>.py`, in snake case, with verbs as sub-commands. Shared logic
lives in the `tools/bof3/` package, and the tests are in `tools/tests/`. A command with no arguments
that every contributor runs is also a Meson run target.
