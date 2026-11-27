# Match one function

Input: `TARGET@0xADDRESS`, for example `emi/world02/area104/14@0x801F4AE4`. This page carries the
match itself; [matching](../../../../docs/matching.md) is the full reference.

1. **Seed.** `tools/seed.py <TARGET>@<func>` writes `work/<image>/<ADDR>/` with the assembly
   (`asm.s`), the header context (`ctx.c`), the best m2c draft, the nearest twins and the callees
   and callers. `work/` is ignored: it is scratch. Read `hints.md` first: it names each detected
   assembly fact and the `docs/matching.md#tactics-for-gcc-272` row it maps to.

2. **Queue.** Build first (`meson compile -C build/meson`): the worklist reads the built images.
   `tools/worklist.py -n 10` lists the open functions; each starts from its m2c draft.
   `bin/coddog match <target> <func>` lists the matched bodies close to it.

3. **Look.** `git grep -l 'func_<ADDR>' -- src` finds the unit's `.c`: read its `INCLUDE_ASM`
   line, its neighbours and the prototypes in the image header. An unknown address or offset:
   `tools/symbol.py at <target> 0x<ADDR>`, `member <Type> 0x<OFF>`, `uses <Name>`. A bare number:
   `tools/symbol.py value 0x<NN> --image <target>` names the enum member or macro that holds it.
   **Check the draft is this function** before tuning it: its size, callees and globals against
   `asm.s`. A draft far off (size outside 0.7-1.4, or most rows differ) often holds a twin's or a
   neighbour's body; write it again from the assembly. Check every constant against the assembly.

4. **Draft.** Write the body in the unit's `.c`, always under `NON_MATCHING`:

   ```c
   #ifdef NON_MATCHING
   NON_MATCHING void func_<ADDR>(void) {
       <body>
   }
   #else
   INCLUDE_ASM(func_<ADDR>);
   #endif
   ```

   Write the SDK's own macros, never their expansion ([SDK names](../../../../docs/conventions.md)):
   `setRGB0`..`setRGB3`, `setXY*`, `setUV*`, `setWH`, `setPolyFT4`/`setSprt`/`setTile`,
   `setSemiTrans`, `addPrim`, `setRECT`, `setVector`, `getClut`, the `gte_*` macros, and
   `getTPage(tp, abr, x, y)` for an `if (GetGraphType() == 1 || GetGraphType() == 2)` pair of
   page constants (decode both constants into one argument set). Write it open only when the macro
   changes the bytes, and say so in the attempts row.

5. **Measure.** `tools/match.sh <target> <func>` compiles the unit and compares the function's
   `.text` with retail: `match` or the first differing instruction, in about 0.1 s. Exit 0 is a
   match, 1 a difference, 2 when nothing was compared (the message names the next step).
   `tools/match.sh --diff <target>@<func>` prints the function side by side, `!` on differing rows;
   the rows are positional, so an inserted instruction marks everything after it. After a new
   `hand/` file, a header or a marker, run `meson setup --reconfigure build/meson` once
   ([reconfigure](../../../../docs/toolchain.md#reconfigure)). A function that reads
   its unit's own `.rodata` (a jump table or a string) is measured too, but `match.sh` does not
   compare a jump table's contents and passes a switch whose table has no `splat.yaml` row: only
   `BOF3_CC_CACHE=0 meson compile -C build/meson check-<image>` proves a match. Give each
   jump-table function its own unit and `.rodata` row. One that reads the unit's
   own `.data` or `.bss`, or the gp, needs the `cc` wrapper
   ([compiler wrapper](../../../../docs/toolchain.md#compiler-wrapper)).

6. **Tactics.** The [tactics table](../../../../docs/matching.md#tactics-for-gcc-272) maps each
   retail shape to the C that produces it. On a miss, label the first hunk
   ([diagnose](../../../../docs/matching.md#diagnose)) and fix it by label. Helpers come after pure C
   fails, benign before harmful, each with its `FAKE:` note
   ([helpers](../../../../docs/matching.md#fake-match-helpers)); a near match goes to the
   [permuter](../../../../docs/matching.md#permuter), which rarely closes a register or order
   difference; name the compiler pass first (below). `__builtin_memcpy` is not 1997 source: write a
   constant copy into a local as `memcpy(dst, src, size)`. A `FAKE_REG` is not source either:
   measure the plain, `register`, width, declaration-order and inlined forms before keeping one.

   **A near miss** (the same instructions, other registers or order) is a question about one
   compiler pass. Name the pass, then change what that pass reads; do not permute spellings.

   - *Which saved register a value gets*: the allocator ranks a value by its uses over the length it
     lives. Count both for the two values that swap, then move a last use earlier, a first use later,
     or route a use through a `u8` or `s16` local so it stops counting.
   - *Where an instruction sits in a block*: the scheduler reorders stores, loads and constant loads
     inside a block, and moves a value across a call only when it already lives across some call.
     Test the statement orders. An unfilled load-delay `nop` means something could not move: a scalar
     load (`LOW(member)`) stays behind a global store, a struct member load does not.
   - *A reload or reuse of a global pointer*: reuse stops at a join. A `for` loop has one after it
     (its entry test) while GCC decides; a `do`-`while` has none.
   - *Two values derived from the loop counter*: they are set up in reverse statement order, and a
     value assigned on every path merges with `i++`; assign them inside the `if`.
   - *A register reused as a constant in a compare*: reuse does not cross widths; make the flag `u8`.
   - *One odd instruction after everything else matches*: read what the form implies about the
     source (a raw `andi` beside an `andi 0xFF` copy is an `s32` parameter with a `u8` local).

   Ask the compiler before guessing. `tools/rtl_dump.sh <file.c> [letters] [function]` prints the
   function's part of GCC's dumps (`l` local, `g` global allocation, `L` loop, `S` schedule,
   `c` combine, `s` cse, `j` jump): `.lreg` lists each pseudo-register with its uses and hard
   register; `.greg` gives the allocation order, conflicts and spills; `L` shows what the loop pass
   moved out and why (a value moves when `threshold * uses * life >= loop size`, and each move
   lowers the threshold by 3 for the values after it). `tools/alloc_priority.py <file.c> <func>`
   ranks the values that live across a call by allocator priority. For a large function run
   `tools/opcode_diff.py <target>@0x<ADDR>` first and fix the structural hunks top-down before
   reading any register. `tools/match_context.sh <target>@0x<ADDR>` prints the assembly, the
   recorded attempts and the C file together.

   Script the forms: write the body once with its variable parts as a table, build each with
   `tools/match.sh --diff`, accept only a line that begins `match:`, then `check-<image>`.
   `tools/try_variants.py <target>@0x<ADDR> <file.c> variants.py` does it for full bodies.

7. **Accept.** Replace the draft with a plain `MATCH` definition, or `HAND_ASM` for authored
   assembly ([markers](../../../../docs/matching.md#markers-and-unmatched-bodies)), and name it
   from evidence or keep `func_<ADDR>` ([natural names](name.md#natural-names)). After three
   structurally different tries, keep the closest draft under `NON_MATCHING` (it must compile with
   `-DNON_MATCHING`) and append a row with `tools/attempts.py add` (it writes `config/attempts/<branch>.jsonl`) with the form reached and the
   first differing instruction; `check-markers` refuses a new draft without one. Then `format` and `pre-push` decide
   ([gates](../SKILL.md#rules-for-every-job)).

**Before you report.**

- The gate ran on this exact head: `meson compile -C build/meson pre-push` after the last commit, on
  the current base ([gates](../../../../docs/matching.md#gates), [pre-push](../../../../tools/README.md#pre-push)).
- The attempts files keep every row they had; a new try appends one with `tools/attempts.py add` (step 7).
- No `config/**/splat.yaml`, header, target-map or compiler-config edit unless the task's `writes`
  list names it; otherwise a `needs: config` line ([rule 4](../../../../AGENTS.md#standing-rules)).
- A report names a function only when it matched; a miss is an escalation, not a report.
- The diff against the base holds only the granted paths and no body that already landed on `main` ([rule 1](../../../../AGENTS.md#standing-rules)).
- The report carries the real head and the matched functions.
- A type or prototype lives in its owner header, once ([layout](../../../../docs/layout.md)).
