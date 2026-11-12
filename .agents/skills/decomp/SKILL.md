---
name: decomp
description: bof3-decomp jobs, chained - match a function (TARGET@0xADDRESS) to the retail bytes, name a symbol from evidence, refactor with the bytes unchanged, research a retail-bytes question read-only, review a diff, tool - change tools/, build files, docs or skills. Use for every task in this repo.
---

# bof3-decomp jobs

Find the job in the table, read its reference, run its chain. Each chain ends in `review`.

## Rules for every job

1. Input: the task `scope` and its `writes` list, the paths it lets you change
   ([rule 1](../../../AGENTS.md#standing-rules)). Anything outside it is a `needs:` line.
2. Bytes stay identical. Every touched image stays EXACT. Only `check-<image>` exit 0 accepts a
   change; a score, a marker or `tools/match.sh` is a lead ([gates](../../../docs/matching.md#gates)).
3. Gates: `check-<image>` for each touched image ([commands](../../../docs/toolchain.md#commands)),
   then `meson compile -C build/meson pre-push`, which runs `check` and the other push checks
   (`check_names`, `check_markers`, `check_tree`, `quality`, `kept`); a failure names its check and
   leaves `build/pre-push/<check>.log`.
4. Report: the result and the evidence for it. A chain gives one report. Last line
   `READY <sha>` or `BLOCKED <reason>`.
5. Game knowledge: the [wiki](https://raulcorreia7.github.io/bof3-wiki/) for a name, a mechanic or
   a table; cite each hit where it is used.

## Jobs

| Job                                                | Reference                                   | Chain                                                                                        |
| -------------------------------------------------- | ------------------------------------------- | -------------------------------------------------------------------------------------------- |
| match a function                                   | [match](references/match.md)                | match → name (each landed function whose callers, reads or constants give evidence) → review |
| polish matched C, twins, repeated code, a constant | [refactor](references/refactor.md)          | refactor → review                                                                            |
| names                                              | [name](references/name.md)                  | name → refactor (share the twins a name unlocks) → review                                    |
| types                                              | [refactor](references/refactor.md)          | refactor → name → review                                                                     |
| tools, build files, docs, prompts                  | [tool](references/tool.md)                  | tool → review                                                                                |
| a question about the retail bytes                  | [research](references/research.md)          | research alone                                                                               |
| a diff or landed range                             | [review](references/review.md)              | review alone                                                                                 |
| a pull request                                     | [review](references/review.md#pull-request) | review (quality pass, then pull request) alone                                               |

## Flow

```text
input ← job, scope, writes list (research: one question, its target)
pick the row → read its reference
loop: run the next job of the chain → until the row's last job has run
gate: check-<image> for each touched image → pre-push
stop: READY <sha> (every touched image EXACT) | BLOCKED <reason> with the first difference or a needs: line
```
