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
| Rank the open functions, cheapest route first | `tools/worklist.py -n 10 [--image <glob>]`                          | `--help`                                                  |
| List one lane's open functions in match order | `tools/worklist.py --image <glob> [--except <name>] --order strategy [--measure]` | `--help`                                                  |
| Write rows for another program           | `<tool> --jsonl` (worklist, dups, sigs, quality `--queue`, symbol refs, template_diff, m2c_sweep) | `--help`                                                  |
| Run every check before a push            | `meson compile -C build/meson pre-push`                                  | [pre-push](#pre-push)                                     |
| Compare one function with retail         | `tools/match.sh <target>@0x<ADDR>`                                       | [match.sh](../docs/toolchain.md#matchsh)                  |
| Preprocess the context for m2c or a scratch | `tools/m2ctx.py include/common.h -o ctx.c`                            | [m2c](../docs/toolchain.md#m2c)                           |
| Draft and upload                         | m2c draft, then a decomp.me scratch with the project flags               | [m2c](../docs/toolchain.md#m2c), [decomp.me](../docs/toolchain.md#decompme) |
| Permute a near match                     | `tools/permuter_import.py src/<path>/<Name>.c`                           | [permuter](../docs/toolchain.md#permuter)                 |
| Run the near-miss loop                   | `tools/near_miss.sh <target>@0x<ADDR> src/<path>/<Name>.c [SECONDS]`     | [permuter](../docs/toolchain.md#permuter)                 |
| Find a template for an assembly function | `tools/template_diff.py <target>@<func>`                                 | [template diff](#templates)                               |
| Try the closest template for one function | `tools/template_try.py <target>@<func>`                                 | [template diff](#templates)                               |
| Try templates in batch                   | `tools/template_try.py rows.jsonl`                                       | same                                                      |
| Compare one function by opcode, registers ignored | `tools/opcode_diff.py <target>@0x<ADDR> [context]`                | [match tools](#match-tools)                               |
| Show GCC's register-allocation dumps     | `tools/rtl_dump.sh <file.c> [letters] [func]`                            | same                                                      |
| Rank the values that live across a call  | `tools/alloc_priority.py <file.c> <func>`                                | same                                                      |
| Try several full bodies, stop at a match | `tools/try_variants.py <target>@0x<ADDR> <file.c> variants.py`           | same                                                      |
| Try every single small edit on drafts    | `tools/sweep_edits.py --worklist FILE --jobs N --pairs --out FILE`       | same                                                      |
| Print assembly, attempts and C file      | `tools/match_context.sh <target>@0x<ADDR>`                               | same                                                      |
| Append an attempts row                   | `tools/attempts.py add --function <target>@0x<ADDR> --tried TEXT`        | `--help`                                                  |
| Try one C body for an assembly function  | `tools/try_body.py <target>@<func> body.c`                               | [try body](#try-body)                                     |
| Draft open functions with m2c, keep exact | `tools/m2c_sweep.py --sample 200`, `tools/m2c_sweep.py --image <image>` | [m2c sweep](#m2c-sweep)                                   |
| Write the seed bundle of one function    | `tools/seed.py <target>@<func>`                                          | [m2c sweep](#m2c-sweep)                                   |
| Measure shapes, write bodies for them | `tools/gen_body.py shapes`, `tools/gen_body.py call-seq`                  | [body generators](#body-generators)                       |
| Find twins in one image                  | `bin/coddog match <target> <func> -t 0.95`                               | [coddog](../docs/toolchain.md#coddog)                     |
| Find alike functions across images       | `tools/dups.py near`                                                     | [duplicates](#duplicates-and-names)                       |
| List same-name groups and split names    | `tools/dups.py shared-names`, `tools/dups.py split-names`                | same                                                      |
| Find repeated C bodies in the source     | `ripwire src --clones`                                                   | same                                                      |
| Rename a function or global everywhere   | `tools/symbol.py rename OLD NEW` (an address name: `--image <target> --local`); its layout rows and unit file follow | [rename steps](../docs/naming.md#rename-steps)  |
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
| Generate the message-id header           | `tools/message_ids.py` (`--check`, `--rewrite`, `--seed`, `--list`)    | [messages](../docs/conventions.md#message-ids)            |
| Split a data unit                        | add a `[0xOFFSET, type, name]` row to `config/<target>/splat.yaml`       | [split](../docs/toolchain.md#split)                       |
| Count readability debt, gate touched files | `tools/quality.py`, `--queue`, `--diff BASE`, `--markdown [--update]`                         | [quality](#quality)                                       |
| Check type loss between two revisions    | `tools/typeloss.py HEAD~5 HEAD`                                          | `--help`                                                  |
| Scan prototypes against definitions      | `tools/sigs.py scan`                                                     | `--help`                                                  |
| Format                                   | `meson compile -C build/meson format` (or `tools/format.sh`)             | [toolchain: commands](../docs/toolchain.md#commands)      |
| Write the progress report                | `meson compile -C build/meson report`                                    | [toolchain: commands](../docs/toolchain.md#commands)      |
| Set up a worktree for parallel work      | `tools/worktree.sh --from <checkout> [--dir <dir>] <branch>`             | [worktrees](#worktrees)                                   |
| Read bytes through Rizin                 | `bin/rz <target> 'pdf @ <func>'`                                         | [rizin](../docs/toolchain.md#rizin)                       |

## Templates

A template is a matched C function with the same shape as an assembly function.
`template_diff.py` lists the closest by opcode sequence and prints only the instructions that differ:
`~` same opcode, other operands; `-` only in the template; `+` only in the target.

```sh
tools/template_diff.py emi/plchar/plp016/00@func_801CF610
tools/template_diff.py <target>@<func> <template target>@<template func>
```

`template_try.py` takes one function ref, or rows of `TARGET@NAME<TAB>TEMPLATE@NAME`
(`dups.py near --full --jsonl` writes them, cheapest first). It aligns the template's instructions
with the target's, names the target's symbol where only a relocation differs, writes the target's
literal where only an immediate differs, declares what the body now uses in the image header, then
calls `try_body.py`. Each row prints `EXACT`, `REMAP-EXACT` (after a rename or literal), `FAIL` with
the number of differing instructions and the first difference, or `SKIP`. A kept body is a lead: run
`check-<image>`, name it from evidence and share it
([shared bodies](../.agents/skills/decomp/references/refactor.md#shared-bodies)). Both tools read
`build/func_index.json.gz` (built on first use; `--rebuild` after a build) and need `rapidfuzz`
(`tools/setup.sh --matching`).

### Try body

`try_body.py` puts a C body in place of one `INCLUDE_ASM(<func>);` line, runs `tools/match.sh` and
keeps the edits only on `match`; otherwise it restores each touched file.

```sh
tools/try_body.py <target>@<func> body.c        # or `-` for stdin
tools/try_body.py --batch rows.tsv              # rows: <target>@<func> <TAB> body.c
```

A line `@decl <declaration>` in the body file (an `extern`, a prototype or a `#define`) moves to the
image header, the first include of the C file, unless an include already declares the name. Output:
`EXACT`, `FAIL` with the first difference, or `SKIP`.

## Match tools

Helpers for one function against the retail bytes; each prints its usage with `--help`.

- `opcode_diff.py` aligns the two sides of `match.sh --diff` on opcodes only; the last line is
  `hunks N retail R cand C`.
- `rtl_dump.sh` compiles one C file with `-DNON_MATCHING` and GCC's `-d` letters and prints the
  function's part of each dump. Its flags copy the image build's.
- `alloc_priority.py` lists each value that lives across a call with its allocator priority
  (`floor(log2(uses)) * uses * 10000 / live length`), its register or `STACK` and the insn that sets it.
- `try_variants.py` builds each body of a `variants.py` (`NAME` and a dict `V` of tag to function
  text) in place of the function, stops at the first `match:` and otherwise restores the file.
- `sweep_edits.py` proposes single edits per draft (a local's or parameter's width, `++` or `+= 1`,
  one cast, one swapped statement, declaration or operand, a loop or if/else form, `break` for
  `return`, a local split or merged, a call argument or a shared tail moved), scores each with
  `MATCH_SRC` in a private copy by an opcode-aligned diff (missing, extra and operand-only
  instructions) and writes the ones that match or score lower as JSON lines; `--pairs` combines
  improving edits, `--climb` chains them.
- `match_context.sh` prints the assembly, the last three rows of `config/attempts.jsonl` and the C
  file that holds the function's `INCLUDE_ASM`.

```sh
tools/opcode_diff.py exe/slus_004_22@0x801530D0 2
tools/alloc_priority.py src/engine/area/map/Area_CellDrawRing.c Area_CellDrawRing
```

## m2c sweep

`tools/m2c_sweep.py` drafts open functions with m2c, runs each through `tools/try_body.py` and keeps
the exact ones in `build/m2c_sweep/results.jsonl`. `tools/seed.py <target>@<func>` writes the drafts,
twins, callers and callees of one function into `work/<image>/<ADDR>/`. Both give m2c a typed work
cell: the context declares `g_SpadView`, a pointer to the mode's work record, so drafts name members
instead of `->unkN`; a context without a complete record keeps the raw cell.

## Body generators

`gen_body.py` lifts a branch-free function into calls and stores and writes C from it with the
repo's names. `shapes` counts every `INCLUDE_ASM` function by shape (`call-seq`, `store-seq`, `spad`,
`dispatch`, `straight`, `branch`); `tools/gen_body.py <shape> [rows.tsv] [--dry-run]` writes a
`MATCH` body per member, declares missing globals in the image header and keeps the body only when
`tools/match.sh` reports an exact result. Twins with one body at one address share `<func>.h`; twins
at several addresses print `TWIN` and stay for a naming pass. A body is a lead: run `check-<image>`,
then name it from evidence.

It writes no branch, `jalr` or load through an argument pointer: such a function prints `SKIP` and
its first unlifted instruction. `worklist.py` lists a function on the `generator` route only when
the tool can write its body.

## Duplicates and names

`dups.py near` groups functions with alike opcodes across all images and names the matched template
of each assembly function (`--threshold` default 0.9, `--min-words` default 6); `near --full` writes
one row per assembly function with its cheapest template and `diff_count`. `shared-names` lists one
name that several bodies use, worst first. `split-names` lists byte-equal bodies that carry several
names. Rows are tab-separated, or JSON lines with `--jsonl`. `ripwire src --clones` lists
token-normalized duplicate C bodies.

## Lookup

`symbol.py` answers questions about the symbols; `symbol.py --help` documents each verb:
`at`, `member`, `uses`, `value`, `layers`, `accesses`, `records`, `values --scan`, `signatures`,
`extents` and `homes`. `--jsonl` writes one object per line. The first `uses` query in an image
analyses its Rizin project and caches the references under `build/symbol-xrefs`.

## Quality

`quality.py` counts, per directory and in total: matched functions still named `func_<ADDR>`, `D_`
and `unk_` tokens, raw width casts, harmful fake helpers, bare `do { } while (0)` blocks (`blocks`, trended), `FAKE:` notes, and bodies pasted into
several images under one name (`pasted`, one `Name.h` is the rule) or several names (`twins`).
`--queue` lists files worst first. `--diff BASE` compares BASE (at its merge-base with `--to`,
default `HEAD`) with `--to` and exits 1 when `casts`, `harmful` or `pasted` rose over the touched
files, when a function holds more `D_`/`unk_` tokens (`names`), or when a named body is now
`func_<ADDR>` (`addr`); a new `MATCH` body is exempt. `--gate` picks other metrics. A commit message
line `Quality-Allowed: <path> <metric>` accepts one rise in one file. Old debt in an untouched file
never fails. `report` stores the totals under `quality` in `report.json`.

## Pre-push

`pre_push.sh [BASE_REF]` (Meson target `pre-push`) runs the checks in `tools/gate.txt`, one line each,
and keeps the logs in `build/pre-push/`. CI runs it too. Commit first: the checks compare commits, so
a tree with uncommitted changes fails before any check runs. `BASE_REF` defaults to the newest of
`public/main`, `origin/main` and `main`. This table lists what fails each check.

| Check           | Fails when                                                                              | Needs      |
| --------------- | --------------------------------------------------------------------------------------- | ---------- |
| `check`         | an image differs from its retail SHA-1                                                  | disc       |
| `check-headers` | a public header does not compile alone                                                  | compiler   |
| `objdiff`       | a unit has no compiled object, or the objdiff project cannot be written (about 30 s)   | disc       |
| `check-plain`   | a source does not build as plain C                                                      | compiler   |
| `check-tree`    | an added line has a register pin, decompiler local, stack name, task offset, m2c macro, raw address, duplicate prototype, wrong header guard or shared body; a prototype differs from its definition without a `sig-kept:` note; a tracked file is game data or over 1 MiB, a relative include or import, an old-style (K&R) definition, or an enum member | none |
| `externs`       | a `.c` file gains an `extern` line                                                      | none       |
| `check-asm`   | there are more `INCLUDE_ASM` lines than at the base ref, in total or in one image       | none       |
| `format-check`  | C, Python, TOML or Markdown differs from the formatter                                  | none       |
| `shell`         | a script of `tools/` or `bin/` has a syntax error, or a `tools/` script a ShellCheck warning | none |
| `test`          | a tool test fails                                                                       | none       |
| `typeloss`      | a rename, move or retype weakens a type                                                 | none       |
| `markers`       | a definition in `src/` lacks exactly one status marker, a change adds a `NON_MATCHING` draft with no `config/attempts.jsonl` object, or an `attempts.jsonl` row carries other keys or another key order | none |
| `drafts`        | a `.c` file the change touches holds a `NON_MATCHING` draft that does not compile with `-DNON_MATCHING` | compiler   |
| `names`         | a new name carries an 8-digit address, a listed legacy one is gone, an added line names a parameter `argN`, or a changed image keeps an address-named layout row for a named symbol | none |
| `addrs`         | a symbol address that `config/symbols/<image>.toml` records on `main` is gone                   | none       |
| `kept`          | a named helper, define, global, type, member or function is lost or degraded; a `FAKE_` name may go | none       |
| `matches`       | a function that is `MATCH` C at the base is not at an address of its image, without `Match-Removed:` | none       |
| `quality`       | a touched file gains casts, fake helpers, `func_`/`D_` names or pasted bodies           | none       |
| `order`         | declarations or symbols in a changed file are out of their recorded order               | none       |
| `message-ids`   | `include/menu/message_ids.h` is stale, or a message id has no line in `include/msg/messages.def` | none       |
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
| `cc.py`, `psxdecomp/dmpsx.py`                | The compiler wrapper (it caches objects in `~/.cache/bof3-cc`, bounded, `--prune` and `--stats` run by hand; `BOF3_CC_CACHE=0` turns that off) and the DMPSX rewrite |
| `objdiff_config.py`, `rzproject.py`          | Build the objdiff project and the Rizin projects                        |
| `check_addrs.py`, `check_kept.py`, `check_matches.py`, `check_markers.py`, `check_names.py`, `check_asm.sh`, `check_externs.sh`, `check_configured.sh`, `check_plain.sh`, `check_tree.sh`, `check_enum_members.py`, `check_signatures.py` | The bodies of the `addrs`, `kept`, `matches`, `markers`, `names`, `check-asm`, `externs`, `check-headers`, `check-plain` and `check-tree` gates |
| `format.sh`                                  | The body of `format` and `format-check`                                 |

`decomp_yaml.py` writes coddog's manifest and is called by `bin/coddog`, not by the build.
`bin/coddog` finds twins and `bin/rz` reads retail bytes; no other tool does either. `bin/internal/` holds `find-tool` and the binutils wrappers (`as`, `ld`, `nm`, `objcopy`, `objdump`) that the build uses.

## Layout

One flat file per task: `tools/<name>.py`, in snake case, with verbs as sub-commands. Shared logic
lives in the `tools/bof3/` package, and the tests are in `tools/tests/`. The package is pure and typed:
it raises `bof3.errors.Bof3Error` and never prints, exits or starts a process. The only code that
reads files, runs Git or `match.sh`, or exits is `tools/bof3/adapters/` and each tool's `main`,
which parses its arguments, calls the package, prints and returns the exit code. A command with no
arguments that every contributor runs is also a Meson run target.
