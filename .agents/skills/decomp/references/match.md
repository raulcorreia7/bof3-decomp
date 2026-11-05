# Match one function

Input: `TARGET@0xADDRESS` from the task.

1. Route ([order](../../../../docs/matching.md#route)): `tools/worklist.py --image <image>` names the
   cheapest. Generator first (`tools/gen_body.py <shape>`), then a template
   (`tools/template_try.py rows.tsv`, then `tools/template_diff.py <target>@<func>` with up to three
   edits, [templates](../../../../tools/README.md#templates)), then the m2c sweep and seed
   (`tools/m2c_sweep.py`, `tools/seed.py`), then the hand loop below.
   Budget: three structurally different tries, then hint and `BLOCKED`. Dedupe with
   `bin/coddog match <target> <func>` ([coddog](../../../../docs/toolchain.md#coddog)): a matched twin
   is reused and shared ([shared bodies](../../../../docs/conventions.md#shared-bodies)), not lifted
   again; a twin in the same image is `<Name>_<ADDR>` with the group's statement macro as its body.
2. Seed: `tools/seed.py <target>@<func>` writes `work/<image>/<ADDR>/` (assembly, context, the best
   m2c draft, twins, callees, callers; [tools](../../../../tools/README.md#m2c-sweep)). Read it with
   the function's prototypes ([loop](../../../../docs/matching.md#the-loop)) and draft there.
3. Measure: put the draft in the unit's `.c` and run `tools/match.sh <target> <func>`
   ([match.sh](../../../../docs/toolchain.md#matchsh)): `match` or the first differing instruction in
   about 0.1 s; `--diff` before the target prints the whole function side by side, `!` on differing
   rows (positional, so an inserted instruction marks the rest). `match.sh` compares `.text` only. A refusal (exit 2) names the reason; for a function
   with a jump table or data use the `cc` wrapper and objdiff
   ([toolchain](../../../../docs/toolchain.md#compiler-wrapper)). Label the first hunk and fix it by
   label ([diagnose](../../../../docs/matching.md#diagnose)).
4. Helpers only after pure C fails, benign before harmful, each with its `FAKE:` note
   ([helpers](../../../../docs/conventions.md#fake-match-helpers)). A near-match goes to the
   [permuter](../../../../docs/matching.md#permuter).
5. On a match, polish the exact candidate ([polish](../../../../docs/matching.md#polish)) and re-run
   `match.sh`. After a type or signature change also run `tools/sigs.py scan <path>`. Without a
   match, leave a hint above the `INCLUDE_ASM` line: the template tried and the first differing
   instruction.
6. The split: a match changes the unit's `.c` and, for a name, `config/symbols.toml`. The
   `config/<target>/splat.yaml` row stays. Change `splat.yaml` only when the split itself is wrong:
   a span that is the head of a longer function (merge, [order](../../../../docs/matching.md#order-of-work)),
   code inside a `T_*`/`bin` subsegment or a multi-function unit
   ([traps](../../../../docs/matching.md#traps)), or a fully matched unit that still has its hex
   offset name (`git mv` with its row, [unit files](../../../../docs/conventions.md#unit-files)).
   `splat.yaml` is the target map, so the change needs the owner's grant (AGENTS.md rule 4);
   without it, report `needs: split <target> <offset> <reason>`. How to edit it:
   [split](../../../../docs/toolchain.md#split).

Report: `exact` (candidate path, `check-<image>` result), `blocked` (cause, first diff, falsified
hypotheses with measurements, best score, the one lever that would change it) or `needs`
([need lines](../../../../docs/matching.md#residuals)).
