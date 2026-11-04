# Agent rules

bof3-decomp is a matching decompilation of *Breath of Fire III* (US, PS1): readable C89 that compiles to
the retail bytes. A function is `TARGET@0xADDRESS`, for example `exe/slus_004_22@0x8014AA04`; equal
addresses in different targets are unrelated. Authority: the retail binary first, then the manifests
in `config/` and the specs. Setup and the folder map: [README.md](README.md).

Set up with `tools/setup.sh --dev`, then `meson setup build/meson` and `meson compile -C build/meson`
([toolchain](docs/toolchain.md#setup)). Gates run as `meson compile -C build/meson <name>`: `check`
for every image, `check-<image>` for one, with `/` written as `+` (`check-exe+slus_004_22`). Without
the disc only the disc-free checks run ([toolchain](docs/toolchain.md#without-a-disc)).

## The path

1. Find work: `tools/worklist.py -n 10` (cheapest route first; `--image` filters).
2. Match in route order: generator, template, draft ([route](docs/matching.md#route), [`match` skill](.agents/skills/match/SKILL.md)).
3. Prove the image: `meson compile -C build/meson check-<image>`.
4. Check everything: `meson compile -C build/meson format pre-push`.
5. Rebase on `main`, push ([parallel work](#parallel-work)).

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
- A function you give up on keeps a hint above its `INCLUDE_ASM`: the template tried and the first
  differing instruction. `tools/worklist.py` shows it.

## Task routing

| Task                                      | Read                                                                                                                                                |
| ----------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Match or polish one function              | [matching](docs/matching.md), [`match` skill](.agents/skills/match/SKILL.md)                                                                        |
| Type, share a twin, restructure, helpers  | [types](docs/conventions.md#types-and-values), [files](docs/conventions.md#files-and-headers), [`refactor` skill](.agents/skills/refactor/SKILL.md) |
| Name a function, global, type or constant | [names](docs/conventions.md#names), [`name` skill](.agents/skills/name/SKILL.md)                                                                    |
| Tools, build files, docs, prompts         | [toolchain](docs/toolchain.md), [`tool` skill](.agents/skills/tool/SKILL.md)                                                                        |
| Bytes, callers, strings, a question       | [toolchain](docs/toolchain.md#native-tools), [`research` skill](.agents/skills/research/SKILL.md)                                                   |
| Review a diff or a landed range           | [`review` skill](.agents/skills/review/SKILL.md)                                                                                                    |
| Target, compiler, PsyQ, any command       | [toolchain](docs/toolchain.md)                                                                                                                      |

Every page: [docs/README.md](docs/README.md). Run the quality pass
([review](.agents/skills/review/SKILL.md#quality-pass)) on your diff before every report.

## Writing

Docs, comments, commit messages and pull requests follow one standard.

- **What, not how.** Say what a thing does and why. The code shows how.
- **ASD-STE100** is the basis for technical text: short sentences, one instruction per sentence,
  active voice, one term for one concept, numbered steps for a procedure. Exact technical terms
  stay.
- **Orwell's six rules** ("Politics and the English Language", 1946):
  1. Never use a metaphor, simile or other figure of speech that you are used to seeing in print.
  2. Never use a long word where a short one will do.
  3. If it is possible to cut a word out, always cut it out.
  4. Never use the passive where you can use the active.
  5. Never use a foreign phrase, a scientific word or a jargon word if you can think of an everyday
     English equivalent.
  6. Break any of these rules sooner than say anything outright barbarous.
