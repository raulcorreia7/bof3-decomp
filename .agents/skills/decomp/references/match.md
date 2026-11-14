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
   ([reconfigure](../../../../docs/toolchain.md#reconfigure)). A function with a jump table, a
   string or data of its own needs the `cc` wrapper
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

   Ask the compiler before guessing: GCC's own dumps say what it decided. Compile the file with
   `-dl -dg` added to its flags from `build/meson/compile_commands.json`: `<file>.lreg` lists each
   pseudo-register with its uses, the insns it lives across and its hard register; `<file>.greg`
   gives the order the global allocator took them in, their conflicts and each spill. Change the
   source until those numbers put the registers where retail has them.
   For a large function compare opcode sequences first (registers and offsets ignored) and fix the
   structural hunks top-down before reading any register.
   `-dL` prints what the loop pass moved out of each loop and why: a value moves when
   `threshold * uses * life >= loop size`, and each move lowers the threshold by 3 for the values
   after it. A register that holds a constant in the draft and a counter in retail is usually one
   move too many or too few earlier in the loop.

   Script the forms: write the body once with its variable parts as a table, build each with
   `tools/match.sh --diff`, and accept only a line that begins `match:`, then `check-<image>`.

7. **Accept.** Replace the draft with a plain `MATCH` definition, or `HAND_ASM` for authored
   assembly ([markers](../../../../docs/matching.md#markers-and-unmatched-bodies)), and name it
   from evidence or keep `func_<ADDR>` ([natural names](name.md#natural-names)). After three
   structurally different tries, keep the closest draft under `NON_MATCHING` (it must compile with
   `-DNON_MATCHING`) and add an object to `config/attempts.jsonl` with the form reached and the
   first differing instruction; `check-markers` refuses a new draft without one. A later pass
   starts from that draft and replaces it only with a closer one. Then `format` and `pre-push` decide
   ([gates](../SKILL.md#rules-for-every-job)).
