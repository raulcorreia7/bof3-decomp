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
   about 0.1 s. `match.sh` compares `.text` only. A refusal (exit 2) names the reason; for a function
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

Report: `exact` (candidate path, `check-<image>` result), `blocked` (cause, first diff, falsified
hypotheses with measurements, best score, the one lever that would change it) or `needs`
([need lines](../../../../docs/matching.md#residuals)).
