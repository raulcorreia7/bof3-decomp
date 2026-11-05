# Matching

How to match, diagnose and polish one function (`TARGET@0xADDRESS`). The retail bytes are the
verdict; a score, a marker or a disassembler opinion is a lead.

## Route

Take the cheapest route first and move on after one honest try. `tools/worklist.py` ranks the open
functions by route ([find work](../CONTRIBUTING.md#find-work)).

| # | Route           | Command                                                                   | Move on when                                            |
| - | --------------- | ------------------------------------------------------------------------- | ------------------------------------------------------- |
| 1 | Generator       | `tools/gen_body.py <shape> --dry-run`, then without `--dry-run`           | the shape is `branch`, or the body is not `EXACT`       |
| 2 | Template        | `tools/template_try.py rows.tsv` (rows from `tools/dups.py near --full`)  | the row is `FAIL`, or the template has `diff_count` > 3 |
| 3 | Template edit   | `tools/template_diff.py <target>@<func>`, then up to three edits          | three edits leave a difference                          |
| 4 | m2c sweep, seed | `tools/m2c_sweep.py`, `tools/seed.py` ([tools](../tools/README.md))       | no exact body from the seed                             |
| 5 | Hand loop       | m2c draft, `tools/match.sh`, [diagnose](#diagnose), [permuter](#permuter) | three structurally different tries fail                 |

Budget: three structurally different tries per function (a different shape, not a tweak of the same
one). Then leave the hint and report `BLOCKED <reason>`.

A route that gives `EXACT` still needs `check-<image>`, a name from evidence and the shared-body
treatment ([shared bodies](conventions.md#shared-bodies)). When you give up, leave a hint above the
`INCLUDE_ASM` line: the template tried and the first differing instruction, in one or two
sentences. The worklist shows the hint, so the next person starts there.

## Order of work

Fix causes before functions.

- Group the open functions by cause (their `INCLUDE_ASM` rows). A shared fix that unblocks a group
  (header type, struct layout, prototype, data declaration, compiler flag) comes before per-function
  tries.
- Reuse matched twins, similar bodies and idioms already in the tree. Find twins with `bin/coddog`
  ([toolchain](toolchain.md#coddog)); a matched twin is shared, not lifted again.
- Take functions whose callees are exact first, then the smallest. Take high scores first. Run the
  permuter on functions near a match while you work others. Park a stuck function with its cause
  ([residuals](#residuals)).
- A reviewed span that is the head of a longer function is fixed by a `splat.yaml` merge, not by a
  per-function try.
- An SDK, BIOS or hardware unit is classified (`sdk`, `hand-asm` in `config/project.toml`) and
  counted, never recovered as game source.

## The loop

1. Read `asm/<target>/func_<ADDR>.s`, its callers and its prototypes.
2. Draft the C in the ignored scratch folder `work/<image>/<ADDR>/`.
3. Compile it with the `cc` wrapper and diff it against the target object assembled from the split
   asm ([toolchain](toolchain.md#compiler-wrapper), [objdiff](toolchain.md#objdiff)), or edit the
   unit's `.c` and run `tools/match.sh <target> <func>`. It answers in a fraction of a second:
   `match`, or the first differing instruction, retail against candidate
   ([match.sh](toolchain.md#matchsh)). `tools/match.sh --diff <target>@<address>` prints the whole
   function side by side, `!` marking differing rows.
4. Polish an exact candidate in place ([polish](#polish)).
5. Run `check-<image>`.

Only the image link proves bytes; `match.sh` compares `.text` only and refuses a function with a
jump table, string or data of its own. A score and an old comparison prove nothing.

After you add a `hand/` file, a header or a `NON_MATCHING` marker, run
`meson setup --reconfigure build/meson` ([reconfigure](toolchain.md#reconfigure)).

## Gates

| Check             | Command                       | Pass                                              |
| ----------------- | ----------------------------- | ------------------------------------------------- |
| One image's bytes | `check-<image>`               | `sha1sum -c` accepts the linked payload           |
| Every image       | `check`                       | every image matches                               |
| Hygiene           | `format-check`, `include-asm` | format passes; `INCLUDE_ASM` not above merge base |

A failed build or an unsupported flag is a failure, never a match. A percentage only ranks work.

## Markers and unmatched bodies

Every function links from its `.c`. A function without C is one `INCLUDE_ASM(<row>);` line; splat's
`create_c_files` writes that stub for a new code row. Every lifted function carries one status
marker at the start of its definition line, so `git grep -c '^MATCH '` counts the matched
functions: `MATCH` for a byte-exact lift, `NON_MATCHING` for a draft.

A draft builds only with `-DNON_MATCHING`; the matching build links the split assembly:

```c
#ifdef NON_MATCHING
NON_MATCHING void func_<ADDR>(void) {
    /* 87.4%; regalloc: v0/v1 tie */
    <body>
}
#else
INCLUDE_ASM(func_<ADDR>);
#endif
```

A draft stays only when it is structured C under these conventions and its score and first mismatch
are known; otherwise the function is the `INCLUDE_ASM` line, with a one- or two-sentence hint above
it when a lift attempt learned something ([comments](conventions.md#comments)).

An asm-authored original keeps the split assembly as its build path and its C model behind
`#if BOF3_USE_ASM ... #else <model> #endif`; `BOF3_ASM_MATCH=0` compiles the model.

The build passes the image's asm folder as `-DASM_DIR="asm/<target>"` (its `hand` subfolder for
authored assembly), so the macro takes only the unit name. A match removes one `INCLUDE_ASM` line;
`include-asm` fails when the tree has more than the merge base with `origin/main` had. It prints
the ref it used and exits 2 when no such ref exists (`git fetch origin main`).

## Helpers

The shared helpers, inline functions and macro forms, the address seams and the fake-match helpers
with their `FAKE:` note: [helpers](conventions.md#helpers). Matched C keeps the coding conventions
([matching code](conventions.md#matching-code)).

## Diagnose

`objdiff-cli diff` reports the first hunk; label it with one of the labels below. Common causes
outside the labels: types and ABI (widths, signedness, pointer vs array, prototype, argument count,
return type), expression lifetime (hoist, survivor copy, cache vs reread, direct call arguments),
storage (`const`, `volatile`, local vs file-local symbol, declaration order), and the compiler
profile (the `cc` wrapper).

### `branch`

Polarity, if/else order, loop form and the delay slot, which executes before the transfer. If retail
shares a tail that ours cross-jumps, reorder the arms so only the shared instruction merges. A
volatile narrow global read through its non-volatile view (`LOHU`/`LOBU`) can restore a missing mask.

### `imm`

Shape and registers match, an immediate differs. Try the address spelling first (symbol, pointer
local, `VOL`, `MEM`), then access width and signedness, then whether the value is a position,
address, mask, count or index and which symbol owns the base register.

### `insert`

Extra instructions in the candidate. Check access width and symbol spelling before control flow;
compare code size, stack frame and saved registers; separate a slot-count change from register
pressure. If retail loads before the prologue, try if/else of two calls before a ternary. Confirm the
reviewed range and boundary.

### `delete`

Instructions missing from the candidate. Keep the store order of a slot write; otherwise as `insert`.

### `opcode`

Instruction shape differs. Read load width and signedness off the retail bytes; check the declared
global width; keep retail's left-to-right grouping. `lwl/lwr` and `swl/swr` are one aggregate
access, not a byte loop. Check constant division/modulo and multiply-high operand order. COP2 uses
the PsyQ `gte_*` macros, never scalar code. A plausible instruction can be data: confirm the range
is code.

### `regalloc`

Shape matches, registers differ. Try a pointer local or an address recomputed from the index, keep
retail's home order for more than four arguments, and write an index that is initialized once and
stepped in the back-edge delay slot as a `for` counter. Compare frame size and saved-register set.
Use the permuter late; pin a register only with a FAKE note and byte proof.

### `scheduling`

Same instruction multiset, different order; this label wins over the others. Write commutative
operands in retail load order, move a counter decrement into its branch, keep retail's
load-then-store order of adjacent globals. For one unfilled delay-slot nop, one sinking store or one
merged reread, try `MATCH_FAKE_BARRIER()` before more reorders. Several no-effect reorders mean a
priority tie.

### `compiler`

Source model, size, control flow and accesses are right; scheduling, allocation or profile remains.
Test one supported profile at a time against the same source. The chain and the override files are
in [toolchain](toolchain.md#compiler-chain). Never rewrite C to fake an assembler expansion.

## Permuter

For clean C with the right structure whose difference is mostly register allocation; poor at stack
differences. Import with `tools/permuter_import.py <source.c>`
([toolchain](toolchain.md#permuter)), let it search, and restate the best candidate as clean C89,
keeping only the changes the score needs. A zero score is not proof; the image link is.

## Polish

An exact function becomes the most human-accurate C that still byte-matches:

- no pointer math; real types and fields;
- named constants ([values](conventions.md#how-a-value-is-written));
- `for` with init, condition and step; `do`-`while` only when the body must run first; `goto` only
  for a proven shared exit;
- fewest casts and locals;
- evidence-backed names ([names](conventions.md#names)), with the lint score breaking the last tie.

Style: [language and formatting](conventions.md#language-and-formatting).

Within one function, work in this order: symbols in `config/symbols.toml`, constants, types and fields in
the headers, control flow, names, comments. Run `check-<image>` after every step; revert a
step that breaks the match instead of compensating with a helper. A missing type or member is a
`needs: type` line ([types](conventions.md#casts-become-member-access)). Stop when the image check passes
and each remaining finding is `kept: <reason>`.

Across functions, collect every consumer's offsets, widths and strides, then place the type: in the
image header when two or more consumers in one image use it, in `include/<subsystem>/` when proven
across images. A union is only for one offset that holds different proven types.

## Traps

| Symptom                                            | Cause                                         | Fix                                                                                                                                                       |
| -------------------------------------------------- | --------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| a split failure with `Duplicate symbol detected`   | two names for one address in a target's table | search `config/symbols.toml` for `0xADDR`; keep one name, or mark the other `alias = true` (the link still reads it); then `meson compile -C build/meson` |
| a clean diff against stale names                   | `asm/` split before a symbol edit             | `meson compile -C build/meson`; the `.splat.stamp` records the config                                                                                     |
| a target looks complete but a function is unlifted | code inside a `T_*`/`bin` subsegment          | split the subsegment at the function offset, re-splat, lift                                                                                               |
| a function in a multi-function unit never matches  | the byte gate compares the whole subsegment   | split at each `glabel`/`jr $ra` boundary                                                                                                                  |
| a `.rodata` placement fails after declaration      | jump-table entries are code addresses         | fix code size first, then declare the placement                                                                                                           |
| a duplicate looks shared across two overlays       | equal addresses in independent images         | resolve against each caller's load base; consolidate only outside the image                                                                               |
| a green score with a wrong symbol                  | relocations masked                            | read `.rel`; search the symbol maps; only the image link proves                                                                                           |

## Residuals

A parked function records its cause and the prerequisite that resumes it. Missing evidence is not a
cause. A function returns only on new evidence (a header fix, a new approach, a resume condition).

A compiler blocker is the last classification, on negative evidence: source and compiler hashes,
target and range, variants and profiles tried, results, and a resume condition.

A need outside the function is one line: `needs: type <Type>+0xOFF <width> (<n> sites)`,
`needs: symbol <ADDR>`, `needs: header <path>` or `needs: config <what>`.
