# Agent rules

bof3-decomp is a matching decompilation of *Breath of Fire III* (US, PS1): readable C89 that compiles
to the retail bytes. A function is `TARGET@0xADDRESS`, for example `exe/slus_004_22@0x8014AA04`; equal
addresses in different targets are unrelated. Authority: the retail binary first, then the manifests
in `config/` and the specs.

Load the [`decomp` skill](.agents/skills/decomp/SKILL.md) before the first item and run the chain its
job table names. The skill and [matching](docs/matching.md) hold the route, the markers and the gates;
[tools](tools/README.md) holds every command and the push checks; [docs](docs/README.md) lists the
pages.

## Standing rules

1. Change only the paths the task grants in its `writes` list (for a pull request, the files it
   changes). Report anything else as a `needs:` line, for example `needs: type Foo+0x10 4 (3 sites)`,
   and leave it undone. End a report with `READY <sha>` or `BLOCKED <reason>`. Scratch goes in
   `work/<image>/<ADDR>/`. Commit on your own branch; the maintainer merges to `main`.
2. Preserve every matched function's bytes and marker. The retail bytes are the verdict; a score,
   marker or analyzer opinion is a lead.
3. Never hand-edit `build/`, `toolchains/` or a generated file. `inputs/` and `toolchains/` change
   only through `tools/setup.sh`. Never commit `inputs/` media.
4. Header, target-map, layout and compiler-config changes need the owner's instruction or a task
   `writes` list that names the path.
5. Commit headers are `type(scope): subject`, imperative, lowercase start, no final period. Never
   amend, force-push or rewrite shared history.
6. Names come from facts ([evidence](docs/conventions.md#evidence)). With no fact keep the address
   name (`func_<ADDR>`, `unk_<OFF>`); never derive a name from an offset, a width, a count or a tool.
7. Keep tests to a minimum: byte-identity gates and risky pure transforms. Run the checks the task
   names and `check` before the report; the report claims only the checks you ran.
8. Leave what you touch better: fix a stale comment, an unclear name or dead code beside your change
   when it is safe and inside the grant. Report larger finds.
9. Read only what changes the outcome: compact output first (`check-<image>`, `rg -n`, `-q`,
   `--json | jq`), never a whole file or build log.

## Before a push

- One worktree per task ([worktrees](tools/README.md#worktrees)); rebase on `main` before each push.
- Merge `main` right before opening the pull request, so the gate and the diff run on the current base.
- `meson compile -C build/meson format`, then `pre-push` ([checks](tools/README.md#pre-push)).
- A `config/symbols.toml` conflict keeps both sides, one row per symbol per image, in address order.
- A failed try is one line in `config/attempts.jsonl`, never a comment in `src/`.

## Writing

Docs, comments, commit messages and pull requests follow the
[project standard](https://github.com/raulcorreia7/bof3/blob/main/docs/standard.md#writing): present
tense, what and why instead of how, in the game developer's own terms, and Orwell's six rules.
Comments say what, never how: one line, only where a name cannot say it
([standard](https://github.com/raulcorreia7/bof3/blob/main/docs/standard.md#comments)).
