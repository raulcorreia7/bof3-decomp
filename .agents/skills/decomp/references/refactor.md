# Refactor with identical bytes

1. Collect every access or copy across all images: the split assembly, `bin/rz <target> 'axt @ SYM'`
   and `rg -n '\bSYM\b' src include` ([users of a symbol](../../../../docs/toolchain.md#every-user-of-a-symbol)).
   One access proves the access, not the layout. A width must match every access.
2. Choose the form ([unit, fixed-point, enum-member and `U` rules](../../../../docs/conventions.md#how-a-value-is-written)):
   - a type, member or cast: [types](../../../../docs/conventions.md#types-and-values);
   - a value: [values](../../../../docs/conventions.md#values);
   - a declaration, header or file move: [layout](../../../../docs/layout.md#lowest-scope-wins);
   - a twin group: `bin/coddog cluster <target>`, then [shared bodies](#shared-bodies);
   - a repeated operation: [helpers and macros](../../../../docs/conventions.md#helpers-and-macros).
   - a new type, member, global or macro name: [globals, arrays, structs and unions](../../../../docs/naming.md#globals-arrays-structs-and-unions)
     and the [natural-names test](name.md#natural-names).
3. Declare once at the lowest scope, add `ASSERT_SIZE` and an `ASSERT_OFFSET` per proven member,
   convert each consumer, and delete its cast or view. A cast that breaks the match stays as
   `kept: <reason>`.
4. Run `check-<image>` for every image that uses the symbol, after each converted consumer. Share
   only when every member is exact; pull the share back when one diverges.
5. Read the result as its original programmer would have written it
   ([the rule](../../../../docs/conventions.md#write-it-as-the-original-programmer-did)); rewrite any
   line that still reads like decompiler output. Re-run `check-<image>` for every touched image.
6. Gate: `pre-push` passes — every image matches (`check`), every source builds as plain C
   (`check-plain`) and no function falls back to `INCLUDE_ASM`.

A missing shared type outside the grant is a `needs: type <Type>+0xOFF <width> (<n> sites)` line.

## Shared bodies

One original source compiled into several overlays, or one helper called with different arguments,
is written once. An exact twin gets one shared form, chosen by where its members live and what
differs. Find candidates with `bin/coddog cluster <target>` ([coddog](../../../../docs/toolchain.md#coddog)); a group is a candidate set, not one body.

| Members                                                                                | Form                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| -------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Any, body of one statement                                                             | Not shared: each member writes the statement (`SYS_DISPATCH_BYTE(table, step);`).                                                                                                                                                                                                                                                                                                                                                                                |
| One image, same body or values used only before the first branch                       | A `static inline` function in the image header; each member is one call (`Battle_ApplyHalfDamage(0x80);`). The inline reads the globals it uses itself and takes values, not pointers it keeps across a call ([inline measurements](../../../../docs/toolchain.md#inline-functions-and-byte-identity)).                                                                                                                                                          |
| One image, a value used after a branch, loop or join, or a pointer local `p = &GLOBAL` | Each member is a visible definition whose body is one statement macro from the image or group header: `MATCH void func_801EFF8C(void) { g_Task->unk_09 = 0; BMagic_NextStep(); }`. A member's extra statements are written in its own body, never passed to the macro as code.                                                                                                                                                                                   |
| Several images, one member each, same source                                           | One function: one game name in every member's `config/symbols.toml` table, the whole definition (`MATCH`, signature, body) in `src/overlays/<group>/<Name>.h`, included at file level where the function sits. The shared file has no include guard.                                                                                                                                                                                                             |
| Several images, a value differs per image                                              | Each member keeps its own `MATCH` function that calls one shared `static inline` helper, or a statement macro where the inline does not match, with the value as an argument: `MATCH void Area_DrawScreenTint(void) { Screen_DrawTintLayer(5, getTPage(0, 2, 960, 0)); }`. The helper takes the fewest arguments needed and never the function name. A per-image `#define` before the include stays only where the difference is a type, with a one-line reason. |
| Several images, one image holds two members                                            | The statement macro for every member of the group, so the body has one source.                                                                                                                                                                                                                                                                                                                                                                                   |
| Several groups, one member each                                                        | One function in the subsystem directory that owns it (`src/shared/Menu_SlidePanelLeft.h`, `src/shared/Actor_FreePaletteFades.h`), not in one user's group. Each member includes it by that path where the function sits (`#include "shared/Menu_SlidePanelLeft.h"`), and the header's first comment lists every member.                                                                                                                                          |
| Several bmagic overlays, same body                                                     | One header `src/overlays/bmagic/<Name>.h`; each overlay's `BMagic_Effect.c` includes it at the body's position.                                                                                                                                                                                                                                                                                                                                                  |
| A helper inside otherwise different functions                                          | A `static inline` function in the group header.                                                                                                                                                                                                                                                                                                                                                                                                                  |

A shared body follows these rules:

- Bodies that differ in a value use a statement macro by default; a `static inline` helper only
  where it gives the same bytes.
- One body lives in `Name.h` at the lowest folder that holds every includer ([layout](../../../../docs/layout.md#tree)), named
  for the function. Each image keeps a thin `Name.c` that includes the image header, then the body.
- A group is a candidate when its members have equal bytes (exact, or equal after relocations).
  Equal text is not enough.
- One name covers every copy. The same address gives the same `func_<ADDR>`; otherwise a name needs
  evidence and one `config/symbols.toml` row per image at that image's address. Two names on
  one body stay unshared until one name is chosen. A second copy in one image is `<Name>_<ADDR>` at
  its own address; both definitions stay visible, and each body is the group's statement macro.
- Bodies that differ share a name only as a role: every member fills the same slot (one installer
  or caller, one signature), and the row's `source` describes the shared role. Otherwise each body takes its own
  name.
- A per-unit compile switch (`TASK_VOLATILE`) stays in the thin `.c`, above the image-header
  include.
- A value that differs per image is a named setting in the image header. A body that needs more
  than one or two settings, or a macro knot, stays per image.
- The most typed copy is the body: struct members over `FIELD` or raw offsets, real parameter types
  over `s32` or `void*`, named locals. If only a less typed copy matches in some image, the group
  stays unshared.
- A body of one statement stays per image. The first comment of a body states what it does and that
  every change must verify every member; the includes are the member list.
- When a function matches, list its group first (`bin/coddog match`); a free twin is a thin `.c`.

Never a body pasted inside `{ }`, a `#define` parameter before the include, an `#undef` after it, an
`#ifndef` default, or `#define NAME func_<ADDR>`. A wrapper is not a match: it compiles as a call.
Share only when every member is exact, verify every member image after an edit, and pull the share
back the moment one diverges. The macro forms: [helpers and macros](../../../../docs/conventions.md#helpers-and-macros).

Report: `typed` or `shared` (record, member or group, the accesses that prove it, owning header),
`kept` (the access that still matches, and why) or `needs`.
