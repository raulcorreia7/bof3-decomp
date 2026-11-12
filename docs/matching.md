# Matching

How to match, diagnose and polish one function (`TARGET@0xADDRESS`). The retail bytes are the
verdict; a score, a marker or a disassembler opinion is a lead.

## Route

Take the cheapest route first and move on after one real attempt. `tools/worklist.py` ranks the open
functions by route, in the tool's order below ([find work](../CONTRIBUTING.md#your-first-match)).

| # | Row         | Route                                                                                          | Move on when                                      |
| - | ----------- | ---------------------------------------------------------------------------------------------- | ------------------------------------------------- |
| 1 | `template0` | `tools/template_try.py <target>@<func>`                                                        | the row is `FAIL`                                 |
| 2 | `generator` | `tools/gen_body.py <shape>`, then without `--dry-run`                                          | the shape is `branch`, or the body is not `EXACT` |
| 3 | `template`  | `tools/template_diff.py <target>@<func>`, then up to three edits                               | three edits leave a difference                    |
| 4 | `plain`     | m2c draft from `tools/seed.py`, `tools/match.sh`, [diagnose](#diagnose), [permuter](#permuter) | three structurally different tries fail           |

A `template0` row is a matched template with no differing instruction; `template` has up to three.
A `generator` row names its shape in the last column. Three structurally different tries per function
— a different instruction count, or a different call or branch sequence — then delete the draft and
record the attempt ([match](../.agents/skills/decomp/references/match.md)).

A route that gives `EXACT` still needs `check-<image>`, a name from evidence and the shared-body
treatment ([shared bodies](../.agents/skills/decomp/references/refactor.md#shared-bodies)).

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
- An SDK, BIOS or hardware unit is classified (`sdk`, `hand-asm` in `tools/objdiff_config.py`) and
  counted, never recovered as game source.

## The loop

1. Read `asm/<target>/func_<ADDR>.s`, its callers and its prototypes.
2. Draft the C in the ignored scratch folder `work/<image>/<ADDR>/`, then move it into the unit's
   `.c` as a `NON_MATCHING` draft ([markers](#markers-and-unmatched-bodies)).
3. Compile it with the `cc` wrapper and diff it against the target object assembled from the split
   asm ([toolchain](toolchain.md#compiler-wrapper), [objdiff](toolchain.md#objdiff)), or run
   `tools/match.sh` ([match.sh](toolchain.md#matchsh)).
4. Polish an exact candidate in place ([polish](#polish)).
5. Replace the draft with a `MATCH` definition and run `check-<image>`. A new lift stays a
   `NON_MATCHING` draft until `tools/match.sh` reports `match` and `check-<image>` passes.

Only the image link proves bytes; a score and an old comparison prove nothing.

A new header, `hand/` file or `NON_MATCHING` marker changes the build graph
([reconfigure](toolchain.md#reconfigure)).

## Gates

| Check             | Command                                                   | Pass                                                                                                                                                                             |
| ----------------- | --------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| One image's bytes | `check-<image>`                                           | `sha1sum -c` accepts the linked payload                                                                                                                                          |
| Every image       | `check`                                                   | every image matches                                                                                                                                                              |
| Hygiene           | `format-check`, `include-asm`, `markers`, `addrs`, `kept` | format passes; `INCLUDE_ASM` not above merge base; every definition marked; no recorded address lost; no named helper, define, global, type, member or function lost or degraded |

A failed build or an unsupported flag is a failure, never a match. A percentage only ranks work.
The full push list, with what fails each check: [tools: pre-push](../tools/README.md#pre-push).

## Markers and unmatched bodies

Every function links from its `.c`. A function without C is one `INCLUDE_ASM(<row>);` line; splat's
`create_c_files` writes that stub for a new code row. Every lifted function carries one status
marker at the start of its definition line, so `git grep -c '^MATCH '` counts the matched
functions: `MATCH` for a byte-exact lift, `NON_MATCHING` for a draft.

A draft builds only with `-DNON_MATCHING`; the matching build links the split assembly:

```c
#ifdef NON_MATCHING
NON_MATCHING void func_<ADDR>(void) {
    <body>
}
#else
INCLUDE_ASM(func_<ADDR>);
#endif
```

Keep a draft under `NON_MATCHING`. Record its attempts in `config/attempts.jsonl`, never in source.

### Status markers

Three markers expand to nothing and say what a definition is; they are not `FAKE:` helpers and
take no `FAKE:` note ([helpers](conventions.md#helpers)).

| Marker         | Meaning                                                      | Shape                                            | Counts as           |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------ | ------------------- |
| `MATCH`        | this C is the original and compiles to the retail bytes      | plain definition                                 | a C match           |
| `NON_MATCHING` | a C draft; the split assembly builds until it matches        | `#ifdef NON_MATCHING` draft, `#else INCLUDE_ASM` | debt                |
| `HAND_ASM`     | the original was hand-written assembly; this C is equivalent | same shape; the `INCLUDE_ASM` is the original    | done, counted apart |

`tools/check_markers.py` requires `HAND_ASM` on every function in `asm/<target>/hand/` and allows
it nowhere else. A `HAND_ASM` body has the same inputs, outputs and effects as the assembly and
keeps a short note with the reason C89 cannot express it.

The build passes the image's asm folder as `-DASM_DIR="asm/<target>"` (its `hand` subfolder for
authored assembly), so the macro takes only the unit name. A match removes one `INCLUDE_ASM` line;
`include-asm` fails when the tree has more than the merge base with `origin/main` had. It prints
the ref it used and exits 2 when no such ref exists (`git fetch origin main`).

## Jump tables

A dense `switch` compiles to a jump table in the unit's `.rodata`. Most overlays keep that table in
the leading data run, before any code, so a lift matches only when the image's layout puts the C
table there:

1. The function's assembly names the table `jtbl_<ADDR>`. Each entry is a word that points into
   the function; the table ends at the first word that does not, which is not always the next row
   the manifest places (two tables can share one data unit).
2. In `config/<image>/splat.yaml`, order `.rodata` where retail has the table (usually
   `section_order: [.data, .rodata, .text, .bss]`) and place the table as its own subsegment at its
   file offset: `- [0xOFFSET, .rodata, <function>]`.
3. Delete those bytes from the data unit that held them.
4. Write the `switch`. `splat` then emits the table into the function's own asm file (the text and
   its table), and the C compiler's table replaces both once the function is `MATCH`.

`tools/match.sh` refuses such a function: its own `.rodata` is not in the partial link. `check-<image>`
is the proof, and the whole-image bytes are the verdict. Placed tables to read before editing:
`world04/area168/13@0x801F4A0C` (a 13-entry table at file offset 0x4),
`world02/area079/13@0x801F2D20` (PR #808) and `world03/area141/13@0x801F2F14` (PR #809).
An image whose `target.toml` has a `[[matching.section_placements]]` row also repeats the address
there (for example `emi/battle/battle/03`).

### A function in a file with other functions

The row pairs the table with the function's own C file: the linker selects
`<function>.c.o(.rodata)`. A function inside a multi-function unit needs its own file first. The
units are contiguous and their files define no statics or data, so split the unit at the table
functions:

1. One `.c` file and one `c` row per block that defines a table function; adjacent blocks without a
   table stay together in a run named after its first function. Copy the unit's preamble (image
   header, the `#if BOF3_USE_ASM` block) into every file and keep each block's comments.
2. Replace the unit's row with one `c` row per piece at the piece's first function address.
3. Place each table as above. While the function is `INCLUDE_ASM`, splat pairs the row with the
   function's text and emits the table into the function's asm file; once the function is `MATCH`,
   the compiler's table occupies the same `.rodata`, selected by the same row.

Worked examples: `scenario/scena06/00`'s `6A0` unit (70 functions, 22 pieces, 18 tables) and
`bmagic/magic060/00`'s `BMagic_Effect` unit (34 functions, 3 pieces, 1 table). `check-<image>`
proves both states. A table in a different segment from its function does not pair
(`etc/start/08`): that one needs the table bytes in the function's own C file until the switch is
written.

## Helpers

The shared helpers, inline functions and macro forms: [helpers](conventions.md#helpers).

### Address seams

These are the only spellings that carry a literal address or offset. Each is a seam to replace with
a symbol or a member once the evidence exists.

| Seam                         | Use                                                                        |
| ---------------------------- | -------------------------------------------------------------------------- |
| `MEM(type, addr)`, `MEM_PTR` | a fixed RAM address with no symbol yet                                     |
| `FIELD(type, base, off)`     | one access at an offset of a base whose type is not proven yet             |
| `HW_REF(type, addr)`         | a hardware register (`include/psx/hw.h` names them)                        |
| `SP*`                        | the scratchpad (`include/sys/scratchpad.h`)                                |
| `VOL(type, x)`               | a volatile access the hardware or a shared buffer needs; not a fake helper |

### Fake-match helpers

Idiomatic C that matches comes first. A fake-match helper is a measured constraint for compiler
behavior C cannot express; `include/match/match.h` defines them and they are inert outside the
matching build. Try in order: correct types and signedness, the original control flow, temporary
lifetimes and declaration order, casts and grouping, the unit's compiler profile, then a helper.

| Group   | Helpers                                                                                                                                                                                       |
| ------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| benign  | `FAKE_VOLATILE_PTR`, `FAKE_BARRIER`, `FAKE_ORDER_LOCK`/`FAKE_ORDER_LOCK_BEGIN`…`FAKE_ORDER_LOCK_END`/`FAKE_ORDER_FENCE`, `FAKE_STACK_PADS` (retail frame bytes nothing explains), `FAKE_HOLD` |
| harmful | `FAKE_REG` (register pin), `FAKE_CLOBBER_*`, `FAKE_OPAQUE`/`FAKE_USE`                                                                                                                         |

Each use carries an adjacent `/* FAKE: <reason>. */`; a dummy local counts as one, and its note
carries the best pure-C score. `FAKE_ORDER_LOCK(stmt)` holds one statement; a run of statements goes
between `FAKE_ORDER_LOCK_BEGIN` and `FAKE_ORDER_LOCK_END;` instead of inside the macro's argument. `FAKE_ORDER_FENCE()` is the empty boundary; write it instead of a bare `do { } while (0);`. Every
helper compiles away without `MATCHING`, and `check-plain` proves the sources build that way. Prefer benign over harmful: a pointer local, a
recomputed address or a statement reorder usually moves the allocator before a pin does. A raw
`__asm__`, a bare `register ... asm("reg")` or a `.word` is not source.

## Matching code

Matched C follows every rule on this page; a match is not a reason to keep the decompiler's shape.
Restate the decompiler output as structured C, then add the least constraint the bytes need, with
its reason. Process and diagnosis: [matching](#diagnose).

**Do**: structured C, named locals, real members.

```c
MATCH void Party_RestoreHp(void) {
    Character* character;
    s32        i;

    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        character     = &g_Characters[g_PartyFieldOrder[i]];
        character->hp = character->max_hp;
    }
}
```

A draft that does not match yet keeps the retail assembly as the build path and records its score
and first mismatch ([markers](#markers-and-unmatched-bodies)). A fake helper is the last
constraint and carries its `FAKE:` note ([helpers](conventions.md#helpers)).

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
merged reread, try `FAKE_BARRIER()` before more reorders. Several no-effect reorders mean a
priority tie.

### `compiler`

Source model, size, control flow and accesses are right; scheduling, allocation or profile remains.
Test one supported profile at a time against the same source. The chain and the override files are
in [toolchain](toolchain.md#compiler-chain). Never rewrite C to fake an assembler expansion.

## Tactics for GCC 2.7.2

The diff says what retail does; this table says what to write for it. Each example is matched C in
`src/`.

| Asm shows                                                    | Write                                                                                                                                                            | Example                               |
| ------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------- |
| the scratchpad pointer loaded once, then reused after a call | assign the pointer to a local after the call, then use the local                                                                                                 | boss051 `func_800C1900`               |
| `lui 0x1F800044` and a load before every access              | a symbol for the cell (`tools/symbol.py add`), read directly each time; a cast of a constant address or of `D_1F800000` makes GCC hoist the base into a register | scena08 `func_801F7B2C`               |
| `andi a0, 0xff` on an argument                               | parameter `s32`, cast at the use: `(u8)dir`                                                                                                                      | area104 `func_801F4AE4.c`             |
| a loop with no entry test, its back edge in the delay slot   | `i = 0; do { ...; i++; } while (i < N);`                                                                                                                         | commu02 `func_801D4F88`               |
| a load, an add, a store, then a test of the old value        | `val = *p; *p = val + 1; if (val < N)`                                                                                                                           | area134 `func_801F3F78.c`             |
| one `lui` base for a read-modify-write                       | `p = &GLOBAL; *p += k;`                                                                                                                                          | shisu `func_801D2CE4`                 |
| two `jal`s with the same arguments                           | write the call twice, no cached local                                                                                                                            | magic069 `func_801EEED4`              |
| N words copied from rodata to the stack, then `jalr`         | `Callback h[N]; __builtin_memcpy(h, TABLE, sizeof(h)); SYS_DISPATCH_BYTE(h, mode);`                                                                              | magic088 `func_801EEC20`              |
| a store, then a reload of the member for the test            | `g_Task->m = f(); if (g_Task->m != 0xFF)`                                                                                                                        | `plchar/Char_ClaimHelperSlotStep.h`   |
| the argument setup disagrees with the prototype              | cast the callee at the call with a `FAKE:` note; the shared prototype stays                                                                                      | `plchar/Char_ClaimHelperSlotStep.h`   |
| a `beq` chain on a state byte                                | `switch` with dense small cases                                                                                                                                  | area197 `func_801F4164.c`             |
| an `andi` mask after a counter update                        | the local is `u8` (likewise `u16` or `s16` for their shifts); plain `char` is unsigned (`-funsigned-char`)                                                       | `engine/game/00/Actor_FindFreeSlot.c` |
| a decrement, a store, then a test of the new value           | decrement inside the test: `if (--x == 0)`                                                                                                                       | scena08 `func_801F7C08`               |
| `bgez` and a `negu` on one value                             | `abs(v)` or `ABS(v)` from `<abs.h>`; retail never calls libc `abs`, so the pair is the inline form and either spelling gives it                                  | `Actor_InitMovement` 0x8015C31C       |
| `bgez` and a `negu` after one computation of a difference    | `abs(a - b)`: `ABS` would recompute the difference on the negative path                                                                                          | `func_80154ABC` 0x80154EA0            |
| `bgez` and a `negu` that writes the destination variable     | the hand-written `if (v < 0) v = -v;`; `ABS(v)` gives a different register                                                                                       | `func_801B21E8`                       |
| `slt` with `beqz` and a `move`                               | `MAX(a, b)` or `MIN(a, b)`; the compare-and-assign `if` gives the same bytes                                                                                     | `func_801BF8E0` 0x801BF8E0            |

A `do`-`while` with a counter and a `goto` are allowed where the bytes need them: `git grep -c
'do {' -- src` totals 558 lines and `git grep -c 'goto ' -- src` 729. `FAKE_REG` is the last
resort, after these forms, and a pin needs its `FAKE:` note and byte proof.

## Permuter

For clean C with the right structure whose difference is mostly register allocation; poor at stack
differences. Import with `tools/permuter_import.py <source.c>`
([toolchain](toolchain.md#permuter)), let it search, and restate the best candidate as clean C89,
keeping only the changes the score needs. A zero score is not proof; the image link is.

## Polish

Polish is part of every match, not a later pass: an exact function lands only after it reads the way
its original programmer wrote it ([the rule](conventions.md#write-it-as-the-original-programmer-did)),
with names still from evidence. It becomes the most human-accurate C that still byte-matches:

- no cast the bytes do not need, and no pointer math: real types and fields (`FIELD` at most);
- no `temp_v0` or `var_s1` names; evidence-backed names ([names](naming.md#names)), with the
  lint score breaking the last tie;
- `g_Task` and its members, not a `WORK` or `SP_PTR` view; `g_Game.members[i]`, not `D_801461xx`;
- named constants ([values](conventions.md#how-a-value-is-written)); decimal for timers, sizes,
  positions and colours; `sizeof` for sizes;
- `for` with init, condition and step; a `do`-`while` or `goto` where the bytes need one
  ([tactics](#tactics-for-gcc-272));
- run `bin/coddog` before matching a function that may have twins ([coddog](toolchain.md#coddog)).

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
