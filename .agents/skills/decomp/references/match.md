# Match one function

Input: `TARGET@0xADDRESS`, for example `emi/world02/area104/14@0x801F4AE4`. This page carries the
whole match; [matching](../../../../docs/matching.md) is the full reference.

1. **Pick a row.** Build first (`meson compile -C build/meson`): the worklist reads the built images.
   `tools/worklist.py -n 10` ranks the open functions, cheapest route first (`template0`,
   `generator`, `template`, `plain`). `--image <substr>` keeps one image, `--route` one route,
   `--tsv` adds the attempts column and `--jsonl` writes the rows as objects. For a `template0` row,
   `tools/template_try.py <TARGET>@<func>` puts the closest matched body in place and measures it.
   A `generator` row names its shape in the last column (`gen_body.py spad`), so run
   `tools/gen_body.py <shape>`; a `template` row also runs `tools/template_diff.py <TARGET>@<func>`
   to see its few differences; a `plain` row starts from the seed's m2c draft.
   `tools/dups.py near --full` lists every template pair; `bin/coddog match <target> <func>` lists
   the matched bodies close to it (`-t 0.5` widens the list). A matched twin is shared through its
   `Name.h` body, never pasted ([shared bodies](refactor.md#shared-bodies)).

2. **Read.** `git grep -l 'func_<ADDR>' -- src` finds the unit's `.c`; read its `INCLUDE_ASM`
   line, its neighbours and the prototypes in the image header. `tools/seed.py <TARGET>@<func>`
   writes `work/<image>/<ADDR>/` with the assembly (`asm.s`), the header context (`ctx.c`), the best
   m2c draft, the nearest twins, and the callees and callers. `work/` is ignored: it is scratch, not
   source.

3. **Draft.** Write the body in `work/<image>/<ADDR>/`, then put it in the unit's `.c` to measure
   it. A draft is always under `NON_MATCHING`; without it the split assembly builds the function:

   ```c
   #ifdef NON_MATCHING
   NON_MATCHING void func_<ADDR>(void) {
       <body>
   }
   #else
   INCLUDE_ASM(func_<ADDR>);
   #endif
   ```

4. **Measure.** `tools/match.sh <target> <func>` compiles the unit and compares the function's
   `.text` with retail: `match`, or the first differing instruction, in about 0.1 s. Exit 0 is a
   text match, 1 a difference, 2 when nothing was compared (the message says why and names the next
   step). `tools/match.sh --diff <target>@<func>` prints the whole function side by side, with `!`
   on differing rows; the rows are positional, so an inserted instruction marks everything after
   it. After you add a `hand/` file, a header or a `NON_MATCHING` marker, run
   `meson setup --reconfigure build/meson` once
   ([reconfigure](../../../../docs/toolchain.md#reconfigure)). A function with a jump table, a
   string or data of its own needs the `cc` wrapper and objdiff
   ([compiler wrapper](../../../../docs/toolchain.md#compiler-wrapper)).

5. **Tactics.** The [tactics table](../../../../docs/matching.md#tactics-for-gcc-272) maps each
   retail shape to the C that produces it. The five used most:

   - `andi` on an argument: parameter `s32`, cast at the use: `(u8)dir`.
   - an `andi` mask after a counter update, or an `sll`/`sra` pair: the local is `u8`, `u16` or
     `s16`; plain `char` is unsigned (`-funsigned-char`).
   - a store, then a reload of the member for the test:
     `g_Task->m = f(); if (g_Task->m != 0xFF)`.
   - a load, an add, a store, then a test of the old value:
     `val = *p; *p = val + 1; if (val < N)`.
   - a loop with no entry test: `i = 0; do { ...; i++; } while (i < N);`.

   On a miss, label the first hunk ([diagnose](../../../../docs/matching.md#diagnose)) and fix it
   by label. Helpers come after pure C fails, benign before harmful, each with its `FAKE:` note
   ([helpers](../../../../docs/matching.md#fake-match-helpers)); a near match goes to the
   [permuter](../../../../docs/matching.md#permuter).

6. **Three tries, then stop.** A try is a structurally different draft of the whole function: a
   different instruction count, or a different call or branch sequence. A tweak of the same shape,
   a stub, an empty body or a `volatile` placeholder is not a try. After three tries, delete the
   draft, keep the bare `INCLUDE_ASM`, and record the function.

7. **Record.** One line in `config/attempts.jsonl`: an object with the keys `function`, `tried`,
   `first_diff`, `score`, in that order. `tried` lists the forms, one clause each; `first_diff` is
   the first differing instruction or the blocker; `score` is the best matching percentage as a
   number, or `null`. A real line:

   <!-- dprint-ignore -->
   ```json
   {"function": "emi/battle/battle/15@0x800AC01C", "tried": "NON_MATCHING: local enemy, volatile task and direct array forms tried", "first_diff": "0x800AC020, saved register.", "score": null}
   ```

   Never add a hint or "tried" comment to `src/`.

8. **Accept.** Replace the draft with a plain `MATCH` definition, or a `HAND_ASM` one for authored
   assembly ([markers](../../../../docs/matching.md#markers-and-unmatched-bodies)), and run
   `meson compile -C build/meson check-<image>` with `/` written as `+`, for example
   `check-emi+world02+area104+14`. `: OK` means the image links to the retail bytes; that is the
   verdict, and a score, a marker or `match.sh` is a lead. Give the body its name from evidence;
   without evidence keep `func_<ADDR>` ([natural names](name.md#natural-names)).

9. **Gate.** `meson compile -C build/meson format`, then
   `meson compile -C build/meson pre-push`. Both must pass.

10. **Report.** The result and the evidence for it; the last line is exactly one of:

    - `READY 4f2a1c8` — every touched image EXACT, with the matched function or the commit named
      above.
    - `BLOCKED emi/bmagic/magic101/03@0x801EF4DC differs at 0x801EF514 (sll v0,v0,5 after the rsin
      call); attempts line written` — the first difference or the missing piece.
