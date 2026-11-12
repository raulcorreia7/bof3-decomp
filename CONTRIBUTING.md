# Contributing to bof3-decomp

bof3-decomp recovers readable C89 that compiles to the retail bytes of *Breath of Fire III* (US,
PlayStation). A good change keeps those bytes and explains the code with evidence. Open an issue
before a large change, such as a new header layout or a rename across images.

## Set up

[Requirements, set up, build and check](README.md#requirements). One command:

```sh
tools/setup.sh --dev --matching
```

`--matching` adds the twin search, the differ and m2c. Without a disc, add `--no-payloads --no-sdk`.
Keep the disc, the extracted data and the toolchain objects local: Git ignores them and they never
belong in a commit. [`tools/README.md`](tools/README.md) lists every routine task as one command.

## Your first match

A function is `TARGET@0xADDRESS`; `<image>` is the target with `/` written as `+` (`exe/slus_004_22`
is `exe+slus_004_22`). This walkthrough needs a built checkout ([check](README.md#commands)).

1. **Find one.** `tools/worklist.py -n 10` ranks the open functions, cheapest route first. A real row:

   ```text
   emi/etc/commu01/07@0x801D3AA0                   27  m2c draft
   ```

   Take the first row; the route column names the tool to start with ([route](docs/matching.md#route)).

2. **Read.** `tools/seed.py emi/etc/commu01/07@0x801D3AA0` writes the assembly, the best m2c draft,
   the twins, callees and callers to `work/emi+etc+commu01+07/801D3AA0/`. A `.c` may hold several
   `INCLUDE_ASM` lines; `git grep -n 'func_<ADDR>' -- src` finds the right one.

3. **Draft.** Replace that `INCLUDE_ASM(func_<ADDR>);` line with a `NON_MATCHING` body
   ([markers](docs/matching.md#markers-and-unmatched-bodies)); a new header or marker needs one
   reconfigure ([reconfigure](docs/toolchain.md#reconfigure)).

4. **Measure.** `tools/match.sh emi/etc/commu01/07@0x801D3AA0` answers `match` or the first differing
   instruction; exit 0, 1 or 2 is equal, different or nothing compared
   ([match.sh](docs/toolchain.md#matchsh)).

5. **Three tries, then record.** A try is a structurally different draft; after three, delete the
   draft and add one line to `config/attempts.jsonl` ([match](.agents/skills/decomp/references/match.md)).

6. **Accept.** Replace the draft with a `MATCH` definition and run
   `meson compile -C build/meson check-emi+etc+commu01+07`. `: OK` is the acceptance
   ([markers](docs/matching.md#markers-and-unmatched-bodies)).

7. **Gate and commit.** `meson compile -C build/meson format pre-push` must pass. The commit form is
   in [AGENTS: standing rules](AGENTS.md#standing-rules); fill the
   [pull request template](.github/PULL_REQUEST_TEMPLATE.md).

Of the open functions, 2,192 of 2,209 are `plain` route; a `template0` or `template` row starts with
`tools/template_try.py`, a `generator` row with `tools/gen_body.py` ([route](docs/matching.md#route)).

## Before you open a pull request

`pre-push` runs every check, one line each, with a log per check in `build/pre-push/`. The full list,
with what fails each and whether it needs the disc or the compiler, is
[tools: pre-push](tools/README.md#pre-push). Without a disc Meson has no `check`, so `pre-push` skips
it. A docs-only change runs the format checks only.

```sh
meson compile -C build/meson format pre-push    # or tools/pre_push.sh [BASE_REF]
```

## Pull requests

1. Branch from the current `main` and push the branch.
2. Commit once per function or shared body; the commit form is in
   [AGENTS: standing rules](AGENTS.md#standing-rules). No trailers.
3. Keep one topic per pull request. Polish the C first: readable, formatted, typed, twins shared.
4. Fill the [template](.github/PULL_REQUEST_TEMPLATE.md): the targets and addresses, the evidence for
   each new name or type, and the checks you ran.
5. The maintainer reviews against [conventions](docs/conventions.md) and merges; expect requests for
   evidence behind names and for the plain-C form of any helper.

Never commit game data, extracted assets, game executables, PsyQ objects, analysis databases or build
output; change generated files through their generator.

## Questions and reports

Ask in [Discussions](https://github.com/raulcorreia7/bof3-decomp/discussions). Report a bug or a wrong
match as an [issue](https://github.com/raulcorreia7/bof3-decomp/issues/new/choose). Report a security
or conduct problem privately: [SECURITY.md](SECURITY.md), [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## Coding agents

[AGENTS.md](AGENTS.md) and `.agents/skills/decomp/` are optional guidance for coding agents. You do
not need them. In them, "maintainer" is the repository owner, and `READY` and `BLOCKED` end an agent
report.

## License

The source is released under [CC0 1.0](LICENSE). By contributing you dedicate your contribution under
CC0, to the extent you own the rights; do not submit code you did not write or cannot license.
Third-party components keep their own terms: [NOTICE](NOTICE).
