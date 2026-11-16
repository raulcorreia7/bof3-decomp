# Match one function

Input: `TARGET@0xADDRESS`, for example `emi/world02/area104/14@0x801F4AE4`. This page carries the
match itself; [matching](../../../../docs/matching.md) is the full reference.

1. **Seed.** `tools/seed.py <TARGET>@<func>` writes `work/<image>/<ADDR>/` with the assembly
   (`asm.s`), the header context (`ctx.c`), the best m2c draft, the nearest twins and the callees
   and callers. `work/` is ignored: it is scratch. Read `hints.md` first: it names each detected
   assembly fact and the `docs/matching.md#tactics-for-gcc-272` row it maps to.

2. **Routes.** Build first (`meson compile -C build/meson`): the worklist reads the built images.
   `tools/worklist.py -n 10` ranks the open functions by route. A `template0` row:
   `tools/template_try.py <TARGET>@<func>` puts the closest matched body in place and measures it.
   A `generator` row names its shape (`gen_body.py spad`); run it. A `template` row:
   `tools/template_diff.py <TARGET>@<func>` shows its few differences. A `plain` row starts from
   the m2c draft. `tools/dups.py near --full` lists every template pair, and
   `bin/coddog match <target> <func>` the matched bodies close to it.

3. **Look.** `git grep -l 'func_<ADDR>' -- src` finds the unit's `.c`: read its `INCLUDE_ASM`
   line, its neighbours and the prototypes in the image header. An unknown address or offset:
   `tools/symbol.py at <target> 0x<ADDR>`, `member <Type> 0x<OFF>`, `uses <Name>`. A bare number:
   `tools/symbol.py value 0x<NN> --image <target>` names the enum member or macro that holds it.

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

5. **Measure.** `tools/match.sh <target> <func>` compiles the unit and compares the function's
   `.text` with retail: `match` or the first differing instruction, in about 0.1 s. Exit 0 is a
   match, 1 a difference, 2 when nothing was compared (the message names the next step).
   `tools/match.sh --diff <target>@<func>` prints the function side by side, `!` on differing rows;
   the rows are positional, so an inserted instruction marks everything after it. After a new
   `hand/` file, a header or a marker, run `meson setup --reconfigure build/meson` once
   ([reconfigure](../../../../docs/toolchain.md#reconfigure)). A function that reads
   its unit's own `.rodata` (a jump table or a string) is measured too. One that reads the unit's
   own `.data` or `.bss`, or the gp, needs the `cc` wrapper
   ([compiler wrapper](../../../../docs/toolchain.md#compiler-wrapper)).

6. **Tactics.** The [tactics table](../../../../docs/matching.md#tactics-for-gcc-272) maps each
   retail shape to the C that produces it. The six used most:

   - `andi` on an argument: parameter `s32`, cast at the use: `(u8)dir`.
   - an `andi` after a counter update, or an `sll`/`sra` pair: the local is `u8`, `u16` or `s16`;
     plain `char` is unsigned (`-funsigned-char`).
   - a store, then a reload of the member for the test: `g_Task->m = f(); if (g_Task->m != 0xFF)`.
   - a load, an add, a store, then a test of the old value: `val = *p; *p = val + 1; if (val < N)`.
   - a loop with no entry test: `i = 0; do { ...; i++; } while (i < N);`.
   - primitive fields stored in order, or a `GetGraphType()` ladder picking a texture page: the
     SDK macro (`setXY4`, `setRGB0`, `setUVWH`, `getTPage(tp, abr, x, y)`); measure it, and keep
     plain assignments only where the macro's order differs from retail.

   On a miss, label the first hunk ([diagnose](../../../../docs/matching.md#diagnose)) and fix it
   by label. Helpers come after pure C fails, benign before harmful, each with its `FAKE:` note
   ([helpers](../../../../docs/matching.md#fake-match-helpers)); a near match goes to the
   [permuter](../../../../docs/matching.md#permuter). `__builtin_memcpy` is not 1997 source: a
   constant copy into a local is written `memcpy(dst, src, size)`, which this compiler expands to
   the same bytes. A `FAKE_REG` is not source either: measure the plain, `register`, width,
   declaration-order and inlined forms before keeping one.

   **A near miss** (the same instructions, other registers or order) is a question about one
   compiler pass. Name the pass, then change what that pass reads; do not permute spellings.

   - *Which saved register a value gets*: the allocator ranks a value by its uses over the
     length it lives. Count both for the two values that swap, then move a last use earlier, a
     first use later, or route a use through a `u8` or `s16` local so it stops counting.
   - *Where an instruction sits in a block*: the scheduler reorders stores, loads and constant
     loads inside a block, and moves a value across a call only when that value already lives
     across some call. The order of stores in the assembly is not the source order: test the
     statement orders. An unfilled load-delay `nop` means something could not move: a scalar
     load (`LOW(member)`) stays behind a global store, a struct member load does not.
   - *A reload, or a reuse, of a global pointer*: reuse stops at a join. A `for` loop has one
     after it (its entry test) while GCC decides; a `do`-`while` has none.
   - *Two values derived from the loop counter*: they are set up in reverse statement order,
     and a value assigned on every path merges with `i++`; assign them inside the `if`.
   - *A register reused as a constant in a compare*: reuse does not cross widths; make the
     flag `u8`.
   - *One odd instruction after everything else matches*: read what the form implies about the
     source (a raw `andi` beside an `andi 0xFF` copy is an `s32` parameter with a `u8` local),
     then fix the registers it disturbs with the rules above.

   Ask the compiler before guessing: GCC's own dumps say what it decided.
   `tools/rtl_dump.sh <file.c> [letters] [function]` compiles the file with the build's flags and
   prints the function's part of each dump (`l` local, `g` global allocation, `L` loop, `S`
   schedule, `c` combine, `s` cse, `j` jump): `.lreg` lists each pseudo-register with its uses,
   the insns it lives across and its hard register; `.greg` gives the order the global allocator
   took them in, their conflicts and each spill. `tools/alloc_priority.py <file.c> <func>` ranks
   the values that live across a call by allocator priority with the register each got. Change the
   source until those numbers put the registers where retail has them.
   For a large function run `tools/opcode_diff.py <target>@0x<ADDR>` first: it compares opcode
   sequences (registers and offsets ignored), and the structural hunks are fixed top-down before
   any register is read. `tools/match_context.sh <target>@0x<ADDR>` prints the assembly, the
   recorded attempts and the C file in one go.
   `tools/rtl_dump.sh <file.c> L <function>` prints what the loop pass moved out of each loop and
   why: a value moves when `threshold * uses * life >= loop size`, and each move lowers the
   threshold by 3 for the values after it. A register that holds a constant in the draft and a
   counter in retail is usually one move too many or too few earlier in the loop.
   Entry order: a local assigned once is scheduled next to its first reader, one assigned twice
   stays where the statement is; the first statement copying the last parameter stays at entry.

   Script the forms: write the body once with its variable parts as a table, build each with
   `tools/match.sh --diff`, and accept only a line that begins `match:`, then `check-<image>`.
   `tools/try_variants.py <target>@0x<ADDR> <file.c> variants.py` does it for full bodies.

7. **Accept.** Replace the draft with a plain `MATCH` definition, or `HAND_ASM` for authored
   assembly ([markers](../../../../docs/matching.md#markers-and-unmatched-bodies)), and name it
   from evidence or keep `func_<ADDR>` ([natural names](name.md#natural-names)). After three
   structurally different tries, keep the closest draft under `NON_MATCHING` (it must compile with
   `-DNON_MATCHING`) and add an object to `config/attempts.jsonl` with the form reached and the
   first differing instruction; `check-markers` refuses a new draft without one. A later pass
   starts from that draft and replaces it only with a closer one. Then `format` and `pre-push` decide
   ([gates](../SKILL.md#rules-for-every-job)).

**Before you report.** The reviewer returned 32 heads with changes; these are the classes, most
frequent first.

- The gate ran on this exact head: `meson compile -C build/meson pre-push` after the last commit, on
  the current base (21 heads; [gates](../../../../docs/matching.md#gates), [pre-push](../../../../tools/README.md#pre-push)).
- `config/attempts.jsonl` keeps every row it had; a new try appends one (6; step 7 above).
- No `config/**/splat.yaml`, header, target-map or compiler-config edit unless the task's `writes`
  list names it; otherwise a `needs: config` line (5; [rule 4](../../../../AGENTS.md#standing-rules)).
- A report names a function only when it matched; a miss is an escalation, not a report (3).
- The diff against the base holds only the granted paths and no body that already landed on `main` (4;
  [rule 1](../../../../AGENTS.md#standing-rules)).
- The report carries the real head and the matched functions (2).
- A type or prototype lives in its owner header, once (2; [layout](../../../../docs/layout.md)).
