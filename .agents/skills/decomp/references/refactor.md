# Refactor with identical bytes

1. Collect every access or copy across all images: the split assembly, `bin/rz <target> 'axt @ SYM'`
   and `rg -n '\bSYM\b' src include` ([users of a symbol](../../../../docs/toolchain.md#every-user-of-a-symbol)).
   One access proves the access, not the layout. A width must match every access.
2. Choose the form ([unit, fixed-point, enum-member and `U` rules](../../../../docs/conventions.md#how-a-value-is-written)):
   - a type, member or cast: [types](../../../../docs/conventions.md#types-and-values);
   - a value: [values](../../../../docs/conventions.md#values);
   - a declaration, header or file move: [layout](../../../../docs/conventions.md#lowest-scope-wins);
   - a twin group: `bin/coddog cluster <target>`, then
     [shared bodies](../../../../docs/conventions.md#shared-bodies);
   - a repeated operation: [helpers and macros](../../../../docs/conventions.md#helpers-and-macros).
   - a new type, member, global or macro name: [globals, arrays, structs and unions](../../../../docs/conventions.md#globals-arrays-structs-and-unions)
     and the [natural-names test](name.md#natural-names).
3. Declare once at the lowest scope, add `ASSERT_SIZE` and an `ASSERT_OFFSET` per proven member,
   convert each consumer, and delete its cast or view. A cast that breaks the match stays as
   `kept: <reason>`.
4. Run `check-<image>` for every image that uses the symbol, after each converted consumer. Share
   only when every member is exact; pull the share back when one diverges.
5. Read the result as its original programmer would have written it
   ([the rule](../../../../docs/conventions.md#write-it-as-the-original-programmer-did)); rewrite any
   line that still reads like decompiler output. Finish with `pre-push`: every image matches
   (`check`), every source builds as plain C (`check-plain`) and no function falls back to `INCLUDE_ASM`.

A missing shared type outside the grant is a `needs: type <Type>+0xOFF <width> (<n> sites)` line.

Report: `typed` or `shared` (record, member or group, the accesses that prove it, owning header),
`kept` (the access that still matches, and why) or `needs`.
