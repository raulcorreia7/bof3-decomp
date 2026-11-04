# Contributing to bof3-decomp

bof3-decomp recovers readable C89 that compiles to the retail bytes of *Breath of Fire III* (US,
PlayStation). A good change keeps those bytes and explains the code with evidence.

## Ways to help

| You have        | Start with                                                                                                                                                  |
| --------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| No disc         | Fix a docs page; improve the [BOF3 wiki](https://github.com/raulcorreia7/bof3-wiki); add a test to [bof3-tools](https://github.com/raulcorreia7/bof3-tools) |
| A disc          | [Match one function](#your-first-match); rename a function or global whose purpose you can prove                                                            |
| A game question | Ask in [Discussions](https://github.com/raulcorreia7/bof3-decomp/discussions)                                                                               |

Open an issue before a large change, such as a new header layout or a rename across images.

## Set up

Follow the [README quick start](README.md#quick-start). The host tools and what each does are in the
[toolchain guide](docs/toolchain.md#host-tools). Keep the disc, the extracted data and the
toolchain objects local: they are ignored by Git and never belong in a commit.

For the permuter, the differ and m2c, run `tools/setup.sh --dev --matching` instead. Setup checks
your disc against [`config/disc.toml`](config/disc.toml) and names each file that differs;
`tools/disc.py verify` repeats the check. Every routine task has one command in
[`tools/README.md`](tools/README.md); `tools/worktree.sh` adds a worktree for parallel work.

## Find work

```sh
tools/worklist.py --image slus_004_22 -n 10      # needs a build: meson compile -C build/meson
```

One row per function still in assembly, cheapest route first: a template with no differing
instruction, a generator shape, a template with a few, then plain matching. `tried:` shows the hint
an earlier attempt left above the `INCLUDE_ASM` line. `--route` and `--image` filter; `--tsv` prints
the full hint. The route order and when to move on: [matching](docs/matching.md#route).

## Your first match

A function is `TARGET@0xADDRESS`; `<image>` is the target with `/` written as `+`
(`exe/slus_004_22` is `exe+slus_004_22`). This walkthrough needs a disc.

1. **Pick a function.** An unmatched function is one `INCLUDE_ASM(func_<ADDR>);` line in its own
   `.c` file. Take the first row of the [worklist](#find-work); its route says which step below to
   start with.

2. **Look for a twin or a template.** A matched body with the same instructions is shared, not
   lifted again. Build once, then search ([coddog](docs/toolchain.md#coddog)). A template is a
   matched function of the same shape; the diff prints only the instructions that differ
   ([templates](tools/README.md#templates)):

   ```sh
   meson compile -C build/meson
   bin/coddog match exe/slus_004_22 func_<ADDR> -t 0.95
   tools/template_diff.py exe/slus_004_22@func_<ADDR>
   ```

3. **Read.** Open `asm/exe/slus_004_22/func_<ADDR>.s` and its callers (`rg -uu 'jal\s+func_<ADDR>' asm/`).
   For a first draft, run [m2c](docs/toolchain.md#m2c) and restate its output as plain C.

4. **Write the C.** In the function's `.c` file, replace the `INCLUDE_ASM` line with a definition.
   Start the definition with the `MATCH` marker, and keep the address name above it:

   ```c
   /* func_8015C9CC */
   MATCH void Actor_ApplyVelocity(void) {
       ...
   }
   ```

   An unnamed function keeps its address name (`MATCH void func_<ADDR>(void)`). Names need
   evidence: [conventions](docs/conventions.md#names). `tools/symbol.py rename` changes a name
   everywhere ([rename steps](docs/conventions.md#rename-steps)).

5. **Compare.** `tools/match.sh` builds the one object and compares the function with retail:

   ```sh
   tools/match.sh exe/slus_004_22@0x<ADDR>
   ```

   Exit 0 means equal. Exit 1 prints the first differing instruction for retail and for your code;
   label it and fix it by label ([diagnose](docs/matching.md#diagnose)). Exit 2 means nothing was
   compared, and the message says why ([match.sh](docs/toolchain.md#matchsh)).

6. **Polish.** Make the code read well while it still matches: real types and members, named
   constants, `for` loops, no pointer math ([polish](docs/matching.md#polish)).

7. **Prove it.** Only the image link accepts a match:

   ```sh
   meson compile -C build/meson check-exe+slus_004_22
   ```

   A function that cannot match yet stays `INCLUDE_ASM`, or a `NON_MATCHING` draft that records its
   score and first mismatch ([markers](docs/matching.md#markers-and-unmatched-bodies)).

A new header, a `NON_MATCHING` marker or an `asm/<target>/hand/` file needs
`meson setup --reconfigure build/meson` ([why](docs/toolchain.md#reconfigure)).

## Before you open a pull request

```sh
meson compile -C build/meson format pre-push    # or tools/pre_push.sh [BASE_REF]
```

`pre-push` runs every check below, one line each, and writes a log per check to
`build/pre-push/`. It compares with the newer of `public/main` and `origin/main`. Without a disc
Meson has no `check`; `pre-push` skips it. Each check:

| Check                    | Fails when                                                                  |
| ------------------------ | --------------------------------------------------------------------------- |
| `check`, `check-<image>` | an image differs from its retail SHA-1                                      |
| `check-headers`          | a public header does not compile alone                                      |
| `check-tree`             | a tracked file is game data or over 1 MiB                                   |
| `include-asm`            | there are more `INCLUDE_ASM` lines than on `main`, in total or in one image |
| `format-check`           | C, Python, TOML or Markdown differs from the formatter                      |
| `meson test`             | a tool test fails                                                           |
| `typeloss`               | a rename, move or retype weakens a type                                     |

The disc-free checks run in CI on every push and pull request through the same entry. A match score,
an analyzer opinion or a decompiler draft is a lead; only `check` proves bytes. For parallel work,
rebase and push, see [AGENTS.md](AGENTS.md#parallel-work).

## Pull requests

- One topic per pull request, with one commit per function or shared body. Polish the C before you
  open it: readable, formatted, typed, twins shared. Do not send one pull request per function.
- Commit subjects are `type(scope): subject`, imperative, lowercase, no final period, for example
  `fix(setup): validate disc tracks`.
- Name the targets and addresses, give the evidence for each new name or type, and list the checks
  you ran. The template has the checklist.
- Change generated files through their generator. Include source and synthetic fixtures only: no
  media, extracted assets, game executables, PsyQ objects or analysis databases.
- The maintainer reviews against [conventions](docs/conventions.md) and merges. Expect requests for
  evidence behind names and for the plain-C form of any helper.

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
