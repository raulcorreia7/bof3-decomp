# Contributing to bof3-decomp

bof3-decomp recovers readable C89 that compiles to the retail bytes of *Breath of Fire III* (US,
PlayStation). A good change keeps those bytes and explains the code with evidence.

## Ways to help

| You have        | Start with                                                                                                                                                  |
| --------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| No disc         | Fix a docs page; improve the [BOF3 wiki](https://github.com/raulcorreia7/bof3-wiki); add a test to [bof3-tools](https://github.com/raulcorreia7/bof3-tools) |
| A disc          | [Match one function](#your-first-function); rename a function or global whose purpose you can prove                                                         |
| A game question | Ask in [Discussions](https://github.com/raulcorreia7/bof3-decomp/discussions)                                                                               |

Open an issue before a large change, such as a new header layout or a rename across images.

## Set up

[Requirements, set up, build and check](README.md#requirements). Keep the disc, the extracted data
and the toolchain objects local: Git ignores them and they never belong in a commit.

- `tools/setup.sh --dev --matching` also installs the permuter, the differ and m2c.
- Setup checks your disc against [`config/disc.toml`](config/disc.toml) and names each file that
  differs; `tools/disc.py verify` repeats the check.
- [`tools/README.md`](tools/README.md) lists every routine task as one command. `tools/worktree.sh`
  adds a worktree for parallel work.

## Your first function

A function is `TARGET@0xADDRESS`; `<image>` is the target with `/` written as `+`
(`exe/slus_004_22` is `exe+slus_004_22`). This walkthrough needs a built checkout
([check](README.md#check) passes).

1. **Find one.** An unmatched function is one `INCLUDE_ASM(func_<ADDR>);` line in its own `.c` file.

   ```sh
   tools/worklist.py -n 10                # or --image slus_004_22
   ```

   One row per function: `TARGET@0xADDRESS`, size in bytes, route, and `tried:` with the attempts
   recorded in `config/attempts.tsv`. Rows are ordered cheapest route first, untried functions first.
   Take the first row. The route says which step to start with ([route](docs/matching.md#route)).
   `--route` and `--image` filter; `--tsv` prints the full attempt text.

2. **Look for a twin or a template.** A matched body with the same instructions is shared, not
   lifted again ([coddog](docs/toolchain.md#coddog)). A template is a matched function of the same
   shape; the diff prints only the instructions that differ ([templates](tools/README.md#templates)):

   ```sh
   bin/coddog match exe/slus_004_22 func_<ADDR> -t 0.95
   tools/template_diff.py exe/slus_004_22@func_<ADDR>
   ```

3. **Read.** Open `asm/exe/slus_004_22/func_<ADDR>.s` and its callers
   (`rg -uu 'jal\s+func_<ADDR>' asm/`). `tools/seed.py exe/slus_004_22@func_<ADDR>` writes the
   assembly, the best m2c draft, twins, callees and callers to `work/exe+slus_004_22/<ADDR>/`
   ([m2c](docs/toolchain.md#m2c)). Restate the draft as plain C.

4. **Write the draft.** In the function's `.c` file, replace the `INCLUDE_ASM` line with a
   `NON_MATCHING` draft. A new lift stays a draft until `tools/match.sh` reports `match` and
   `check-<image>` passes:

   ```c
   #ifdef NON_MATCHING
   /* func_8015C9CC */
   NON_MATCHING void Actor_ApplyVelocity(void) {
       ...
   }
   #else
   INCLUDE_ASM(func_8015C9CC);
   #endif
   ```

   An unnamed function keeps its address name (`NON_MATCHING void func_<ADDR>(void)`). Names need
   evidence: [conventions](docs/naming.md#names). A draft needs
   `meson setup --reconfigure build/meson` once ([reconfigure](docs/toolchain.md#reconfigure)).

5. **Compare.** `tools/match.sh` builds the one object and compares the function with retail:

   ```sh
   tools/match.sh exe/slus_004_22@0x<ADDR>
   ```

   Exit 0: equal. Exit 1: the first differing instruction for retail and for your code; label it and
   fix it by label ([diagnose](docs/matching.md#diagnose)). Exit 2: nothing was compared, and the
   message says why ([match.sh](docs/toolchain.md#matchsh)). Three structurally different tries
   without a match end the attempt: add a row to `config/attempts.tsv` with the columns `function`,
   `tried`, `first_diff` and `score` (tab-separated, quoted), then pick another function
   ([budget](docs/matching.md#route)).

6. **Polish.** Make the code read well while it still matches: real types and members, named
   constants, `for` loops, no pointer math ([polish](docs/matching.md#polish)).

7. **Accept.** After `match.sh` reports `match`, replace the draft with a `MATCH` definition (no
   `#ifdef`, no `INCLUDE_ASM` line). Only the image link accepts it:

   ```sh
   meson compile -C build/meson check-exe+slus_004_22
   ```

   If the check fails, restore the `NON_MATCHING` draft
   ([markers](docs/matching.md#markers-and-unmatched-bodies)).

8. **Check everything.**

   ```sh
   meson compile -C build/meson format pre-push    # or tools/pre_push.sh [BASE_REF]
   ```

9. **Commit and open the pull request.** [Pull requests](#pull-requests) gives the message format
   and the checklist.

## Before you open a pull request

`pre-push` runs every check below, one line each, and writes a log per check to `build/pre-push/`.
It compares with the [base ref](docs/toolchain.md#commands). Without a disc Meson has no `check`;
`pre-push` skips it.

| Check                    | Fails when                                                                             |
| ------------------------ | -------------------------------------------------------------------------------------- |
| `check`, `check-<image>` | an image differs from its retail SHA-1                                                 |
| `check-headers`          | a public header does not compile alone                                                 |
| `check-tree`             | a tracked file is game data or over 1 MiB                                              |
| `include-asm`            | there are more `INCLUDE_ASM` lines than on `main`, in total or in one image            |
| `externs`                | a `.c` file gains an `extern` line                                                     |
| `markers`                | a function definition in `src/` lacks exactly one `MATCH` or `NON_MATCHING` marker     |
| `names`                  | a new name in `include/` or `src/` carries an 8-digit address, or a listed one is gone |
| `addrs`                  | a symbol address that `config/symbols.toml` records on `main` is gone                  |
| `format-check`           | C, Python, TOML or Markdown differs from the formatter                                 |
| `meson test`             | a tool test fails                                                                      |
| `typeloss`               | a rename, move or retype weakens a type                                                |
| `quality`                | a touched file gains casts, fake helpers, `func_`/`D_` names or pasted bodies          |

The disc-free checks run in CI on every push and pull request through the same entry. A match score,
an analyzer opinion or a decompiler draft is a lead; only `check` proves bytes. For parallel work,
rebase and push, see [AGENTS.md](AGENTS.md#parallel-work). A pull request that changes only docs
runs the format checks only.

## Pull requests

1. Branch from the current `main`: `git switch -c match/<image>-<name>`. Push it to your fork.
2. Commit once per function or shared body. The subject is `type(scope): subject`, imperative,
   lowercase, no final period, no trailers. The scope is the source folder. Examples:
   `match(bmagic/magic117): match func_801EF20C from the fade template`,
   `refactor(battle): type the effect target`, `fix(setup): validate disc tracks`.
3. Open a pull request against `main` with one topic. Polish the C first: readable, formatted, typed,
   twins shared. Do not send one pull request per function.
4. Fill the [template](.github/PULL_REQUEST_TEMPLATE.md): the targets and addresses, the evidence for
   each new name or type, and the checks you ran.
5. The maintainer reviews against [conventions](docs/conventions.md) and merges. Expect requests for
   evidence behind names and for the plain-C form of any helper.

Never commit: game data, extracted assets, game executables, PsyQ objects, analysis databases, or
build output. Change generated files through their generator. Include source and synthetic fixtures
only.

## Questions and reports

Ask in [Discussions](https://github.com/raulcorreia7/bof3-decomp/discussions). Report a bug or a
wrong match as an [issue](https://github.com/raulcorreia7/bof3-decomp/issues/new/choose). Report a
security or conduct problem privately: [SECURITY.md](SECURITY.md),
[CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## Coding agents

[AGENTS.md](AGENTS.md) and `.agents/skills/decomp/` are optional guidance for coding agents. You do not
need them. In them, "maintainer" is the repository owner, and `READY` and `BLOCKED` are the words an
agent ends its report with.

## License

The source is released under [CC0 1.0](LICENSE). By contributing you dedicate your contribution under
CC0, to the extent you own the rights; do not submit code you did not write or cannot license.
Third-party components keep their own terms: [NOTICE](NOTICE).
