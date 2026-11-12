# Agent rules

bof3-decomp is a matching decompilation of *Breath of Fire III* (US, PS1): readable C89 that compiles to
the retail bytes. A function is `TARGET@0xADDRESS`, for example `exe/slus_004_22@0x8014AA04`; equal
addresses in different targets are unrelated. Authority: the retail binary first, then the manifests
in `config/` and the specs. Setup and the folder map: [README.md](README.md).

Requirements, set up, build and check: [README](README.md#requirements). Gates run as
`meson compile -C build/meson <name>`: `check` for every image, `check-<image>` for one, with `/`
written as `+` (`check-exe+slus_004_22`). Without the disc only the disc-free checks run
([toolchain](docs/toolchain.md#without-a-disc)).

## The path

1. Find work: `tools/worklist.py -n 10` (cheapest route first; `--image` filters).
2. Match in route order: generator, template, draft ([route](docs/matching.md#route), [`decomp` match](.agents/skills/decomp/references/match.md)).
3. A new lift stays a `NON_MATCHING` draft until `tools/match.sh` reports `match` and
   `check-<image>` passes ([markers](docs/matching.md#markers-and-unmatched-bodies)).
4. Prove the image: `meson compile -C build/meson check-<image>`.
5. Check everything: `meson compile -C build/meson format pre-push`.
6. Rebase on `main`, push ([parallel work](#parallel-work)).

## Standing rules

1. Change only the paths the task grants in its `writes` list (for a pull request, the files it
   changes). Report anything else you need as a `needs:` line, for example
   `needs: type Foo+0x10 4 (3 sites)`, and leave it undone. End an agent report with `READY <sha>`
   (the commit holding the work) or `BLOCKED <reason>`. Scratch goes in `work/<image>/<ADDR>/`.
   Commit on your own branch; the maintainer merges to `main`.
2. Preserve every matched function's bytes and marker. The retail bytes are the verdict; a score,
   marker or analyzer opinion is a lead ([gates](docs/matching.md#gates)).
3. Never hand-edit `build/`, `toolchains/` or a generated file. `inputs/` and `toolchains/` change
   only through `tools/setup.sh`. Never commit `inputs/` media.
4. Header, target-map, layout and compiler-config changes need the owner's instruction or a task
   `writes` list that names the path.
5. Commit headers are `type(scope): subject`, imperative, lowercase start, no final period. Never
   amend, force-push or rewrite shared history.
6. Names come from facts ([naming](docs/conventions.md#evidence)). With no fact keep the address name
   (`func_<ADDR>`, `unk_<OFF>`); never derive a name from an offset, a width, a count or a tool.
7. Keep tests to a minimum: byte-identity gates and risky pure transforms. Run the checks the task
   names and `check` before the report; the report claims only the checks you ran.
8. Leave what you touch better: fix a stale comment, an unclear name or dead code beside your change
   when it is safe and inside the grant. Report larger finds.
9. Read only what changes the outcome: compact output first (`check-<image>`, `rg -n`, `-q`,
   `--json | jq`), never a whole file or build log.

## Parallel work

- One worktree per task: `tools/worktree.sh --from <built checkout> <branch>`
  ([worktrees](tools/README.md#worktrees)). Rebase on `main` before each push.
- A `config/symbols.toml` conflict keeps both sides, one row per symbol per image, in address order.
- `meson compile -C build/meson format` rewrites C, Python, TOML and Markdown and needs clang-format,
  ruff and dprint; `pre-push` only checks.
- In zsh quote word lists (`git grep -lz ... | xargs -0`) and overwrite with `>|`.
- Record failed attempts in `config/attempts.jsonl`: the forms tried and first differing instruction.
  `tools/worklist.py` shows them.

## Task routing

| Task                                      | Read                                                                                                                                                        |
| ----------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Match or polish one function              | [matching](docs/matching.md), [`decomp` match](.agents/skills/decomp/references/match.md)                                                                   |
| Type, share a twin, restructure, helpers  | [types](docs/conventions.md#types-and-values), [files](docs/layout.md#files-and-headers), [`decomp` refactor](.agents/skills/decomp/references/refactor.md) |
| Name a function, global, type or constant | [names](docs/naming.md#names), [`decomp` name](.agents/skills/decomp/references/name.md)                                                                    |
| Tools, build files, docs, prompts         | [toolchain](docs/toolchain.md), [`decomp` tool](.agents/skills/decomp/references/tool.md)                                                                   |
| Bytes, callers, strings, a question       | [toolchain](docs/toolchain.md#native-tools), [`decomp` research](.agents/skills/decomp/references/research.md)                                              |
| Review a diff or a landed range           | [`decomp` review](.agents/skills/decomp/references/review.md)                                                                                               |
| Target, compiler, PsyQ, any command       | [toolchain](docs/toolchain.md)                                                                                                                              |

Every page: [docs/README.md](docs/README.md). Run the quality pass
([review](.agents/skills/decomp/references/review.md#quality-pass)) on your diff before every report.

## Index

Everything an agent can read, in one list.

- Skill: [.agents/skills/decomp/SKILL.md](.agents/skills/decomp/SKILL.md). Its references:
  [match](.agents/skills/decomp/references/match.md), [name](.agents/skills/decomp/references/name.md),
  [refactor](.agents/skills/decomp/references/refactor.md),
  [research](.agents/skills/decomp/references/research.md),
  [review](.agents/skills/decomp/references/review.md), [tool](.agents/skills/decomp/references/tool.md).
- Tools: [tools/README.md](tools/README.md) lists every tool by task. Every tool takes `--help`.
- Docs: [docs/README.md](docs/README.md) lists every page.
- CI: [.github/workflows/ci.yml](.github/workflows/ci.yml) runs the disc-free checks.
- Wiki (game and format facts): [site](https://raulcorreia7.github.io/bof3-wiki/). For a model: [llms.txt](https://raulcorreia7.github.io/bof3-wiki/llms.txt) (index), [llms-small.txt](https://raulcorreia7.github.io/bof3-wiki/llms-small.txt) (compact, for a small context), [llms-full.txt](https://raulcorreia7.github.io/bof3-wiki/llms-full.txt) (everything).
- Project standard: [docs/standard.md](https://github.com/raulcorreia7/bof3/blob/main/docs/standard.md).

## Writing

Docs, comments, commit messages and pull requests follow the [project standard](https://github.com/raulcorreia7/bof3/blob/main/docs/standard.md#writing): present tense, what and why instead of how, in the game developer's own terms, and Orwell's six rules.
Comments say what, never how: one line, only where a name cannot say it ([standard](https://github.com/raulcorreia7/bof3/blob/main/docs/standard.md#comments)).
