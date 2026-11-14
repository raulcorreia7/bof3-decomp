# Coding conventions

How bof3-decomp code is written. How to match a function: [matching](matching.md). How to name a
thing: [naming](naming.md). Where a file, a header or a symbol goes: [layout](layout.md). How to
build and inspect: [toolchain](toolchain.md).

The code reads as clean, idiomatic C a game programmer of 1998 would write: names for what things
are in Breath of Fire III, real types and members instead of casts and offsets, and plain
statements. A workaround stays only when the retail bytes need it, and its comment says why.

- Evidence decides what a thing is: the retail bytes and their callers, never a guess. Better
  unnamed than named wrongly.
- One name per thing in every image, one definition per name, at the lowest scope that covers its
  users.
- Names in the tree that do not follow this page are renamed over time. An old name is not a pattern
  to copy.

## Quick reference

| Do                                                                                                | Don't                                                         |
| ------------------------------------------------------------------------------------------------- | ------------------------------------------------------------- |
| Tag every name: `SND_PlayCue`, `Battle_ApplyDamage`, `g_BattleActors`                             | Leave a game name untagged, or write `g_BATTLE_Actors`        |
| `Tag_VerbObject`; a family of 3+ is `Tag_ObjectVerb`: `Message_WindowOpen`                        | Glue the subject to the verb: `MessageSelectAnswerOpenMenu`   |
| Keep the address name above a named definition: `/* func_801F2C04 */`                             | Lose the `func_`/`D_` name a search from assembly needs       |
| `snake_case` locals, parameters and members: `item_id`, `party_slot`                              | Hungarian or camelCase: `pItem`, `nCount`, `itemId`           |
| Name the role: `BattlePanel`, `coord_x`                                                           | Name the storage: `BattlePanelRecord`, `half_3A`, `ByteView`  |
| Acronyms keep their capitals: `EnemyAIBlock`, `Char_RestoreHP`, `SYS_ReadCD`                      | Mixed case: `EnemyAiBlock`, `Char_RestoreHp`, `SYS_ReadCd`    |
| A type is an English noun phrase: `EnemyBattler`, `PartyMember`                                   | The tag on a type: `BattlerEnemy`, `BattlerParty`             |
| A slot is a filled position (`party_slot`); a fixed table position is an index (`CharacterIndex`) | `CharacterSlot` for the record array's position               |
| An id is the value the game stores to identify a thing (`item_id`, `character_id`)                | `slot_id`, `item_index` for the stored value                  |
| A fixed array position is an index (`element_index`); never abbreviate it                         | `idx`, `slot_index`, `element_slot`                           |
| A vector type names its element width: `Point3l`, `Point2u`                                       | `Vec3i`, `Vec2us`                                             |
| `mode`/`step`: state phase, `step++`; `timer` counts down; `frame` counts up per frame            | `frame--`, a `timer` that counts up, a per-frame `_step`      |
| A per-frame amount is a `_delta` or `speed`: `vz_delta`                                           | `vz_step`                                                     |
| Keep the address name until a caller proves the role                                              | Guess a name from a count, an offset or a tool's output       |
| Members and typed pointers: `battler->hp`                                                         | Casts and offsets: `*(s16*)((u8*)p + 0x1C)`                   |
| `enum` for closed sets and flag words; `#define` for sizes and limits                             | An `enum` type as a member or parameter (it is an `int`)      |
| Decimal quantities, hex bit patterns: `hp < 100`, `flags & 0x80`                                  | `hp < 0x64`, `flags & 128`                                    |
| Named bits: `INPUT_REPEATED(held, (PADLup \| PADLdown))`                                          | `INPUT_REPEATED(held, 0x5000)`                                |
| PsyQ functions and names directly; game macros for sets and checks                                | Raw SDK numbers, renamed SDK values, raw hardware addresses   |
| Restate decompiler output as structured C with named locals                                       | Keep `temp_v0`, `var_s1`, `goto loop_1` and pointer math      |
| `BYTE_MASK`, `MIN`, `ARRAY_COUNT` and the other `util.h` helpers                                  | A local copy of a helper, or a helper that shadows the SDK    |
| A `static inline` helper for a repeated operation                                                 | A macro where an inline matches the same bytes                |
| Reusable helpers, at most two steps from the real thing                                           | A `#define` that only renames or forwards, or a chain of them |
| Braces on every body; parentheses around bitwise operands                                         | `if (x) y();`, `if (a & B && c)`                              |
| `/* FAKE: <reason>. */` beside every fake-match helper                                            | A bare `register ... asm()`, `__asm__` or `.word` in C        |
| One `extern` in the owning header                                                                 | `extern` in a `.c`, or a second name for one address          |
| [Header layout](layout.md#header-layout): one block per record, in table order                    | Enums after their users, or an ID enum sorted by name         |
| One-line `/* */` comments that say what a name cannot                                             | A comment that restates the name, tells history or evidence   |
| Adjacent globals as one struct, array or union, members by role                                   | Loose globals at one base or stride                           |

## Base layer

The header, macros, records and shared bodies follow the forms common to
[sotn-decomp](https://github.com/Xeeynamo/sotn-decomp),
[silent-hill-decomp](https://github.com/shdecompilations/silent-hill-decomp),
[parasite-eve-decomp](https://github.com/khasinski/parasite-eve-decomp),
[rood-reverse](https://github.com/ser-pounce/rood-reverse),
[parasite-eve-2-decomp](https://github.com/GabeRealB/parasite-eve-2-decomp) and
[psx_tomba](https://github.com/hansbonini/psx_tomba).

### Header

| Rule                                                   | Where              |
| ------------------------------------------------------ | ------------------ |
| One umbrella header every unit starts from             | `include/common.h` |
| Fixed-width types and the type asserts                 | `include/types.h`  |
| No second umbrella and no shared type in `include/psx` | `include/common.h` |

### Utility macros

| Rule                                                               | Where                   |
| ------------------------------------------------------------------ | ----------------------- |
| `ABS` has one definition, the vendored PsyQ form                   | `include/psyq/abs.h`    |
| `ARRAY_COUNT`, `MIN`, `MAX`, `BIT` and the byte and halfword masks | `include/common/util.h` |
| A macro earns its place by a use; no generic helper without one    | `include/common/util.h` |

### Matching helpers

| Rule                                                                               | Where                   |
| ---------------------------------------------------------------------------------- | ----------------------- |
| The 14 `FAKE_*` helpers are the only matching constraints; one form per constraint | `include/match/match.h` |
| Every use carries `/* FAKE: reason. */`                                            | `include/match/match.h` |
| No raw `__asm__`, `register ... asm` or `.word` outside this header                | `include/match/match.h` |

### SDK names

| Rule                                                            | Where                          |
| --------------------------------------------------------------- | ------------------------------ |
| Vendored PsyQ headers stay unmodified                           | `include/psyq`                 |
| Use the SDK function, value and macro name; no second name      | `include/psx/psyq.h`           |
| Use `setXY0` and the `gte_*` macros where the SDK provides them | `include/match/gte_macros.inc` |

### Records

| Rule                                                                           | Where               |
| ------------------------------------------------------------------------------ | ------------------- |
| `field_<OFF>` unknown role, `unk_<OFF>` unknown member, `pad_<OFF>` fill       | the owning header   |
| `/* 0xNN */` before every member; `ASSERT_SIZE` and `ASSERT_OFFSET` per record | `include/types.h`   |
| `FIELD` and `SP_REF` are seams, not a record style                             | `include/psx/mem.h` |

### Shared bodies

| Rule                                                                               | Where                        |
| ---------------------------------------------------------------------------------- | ---------------------------- |
| One body in a header included by a thin `MATCH` `.c` per image                     | `src/shared`, `src/overlays` |
| A value that differs is a statement macro; a structural difference stays per image | the group header             |
| Never `#include` a `.c` file                                                       | `src`                        |

### Files and names

| Rule                                                                                         | Where               |
| -------------------------------------------------------------------------------------------- | ------------------- |
| Functions `Tag_VerbObject`; `g_` globals; `s_` statics; PascalCase types; snake_case members | [naming](naming.md) |
| Constants `SCREAMING_SNAKE`; files lower snake by role                                       | [naming](naming.md) |
| No evidence: `func_<ADDR>`, `D_<ADDR>` or `unk_<OFF>`                                        | [naming](naming.md) |

## Write it as the original programmer did

Every type, struct, member, value and helper reads the way the game's programmer wrote it in 1997:

- Records are built from nested structs (`pos`, `stats`, `equip`).
- Values are game enums or named constants.
- Arithmetic uses compound operators (`hp -= damage`).
- Fixed-point halves go through `COORD_INT()`.
- One typed local replaces repeated casts.
- Helpers declare their own locals.
- Any line that still looks like decompiler output gets rewritten, then byte-checked.

## Language and formatting

Plain C89. The one GNU extension is `static inline` where it gives the retail bytes
([compiler chain](toolchain.md#compiler-chain)); the build's `INCLUDE_ASM` and `__attribute__` layout fixes are tooling, not source style.
A table indexed by an enum lists its rows in enum order with a one-line `/* NAME */` before each,
never a designated initializer. No mixed declarations and code, no declarations in `for`, no `_Bool`, no anonymous
unions, no `//` comments.

The layout: 4-space indent, 200 columns, braces on the same line, `T* x` pointers, declarations and
assignments aligned within each block. The formatter owns it, so never hand-align
([format](toolchain.md#commands)).

A function reads in blocks, like its pseudocode: the declarations, then one block per step (set up,
loop, finish), with one blank line between blocks and none at the start of a block. The order,
the loops and the stop conditions show at a glance. The formatter keeps at most one blank line and
never adds one inside a function, so the blocks are yours to place. Blank lines never change the
bytes.

- Every `if`, `else`, `for`, `while` and `do` body has braces, even one statement.
- A bitwise expression inside a comparison or a logical operator is in parentheses.
- `for` has its init, condition and step. A `do`-`while` or `goto` is allowed where the retail bytes
  need one ([tactics](matching.md#tactics-for-gcc-272)).

**Do**

```c
if ((battler->flags & BATTLER_FLAG_KO) != 0 && battler->hp == 0) {
    return;
}

for (i = 0; i < PARTY_SLOT_COUNT; i++) {
    Party_ResetMember(i);
}
```

**Don't**

```c
if (battler->flags & BATTLER_FLAG_KO && battler->hp == 0) return;
i = 0;
while (i < 3) { Party_ResetMember(i); i++; }
```

## Ids

An id is the fixed-width integer the retail data stores, named `<thing>_id`; its values are
constants in an anonymous `enum` whose comment names the table they index. No typedef per id: in C
it checks nothing that `item_id` does not already say, and an `enum` type would change the width
([compiler chain](toolchain.md#compiler-chain)). Each retail table has its own constants: `ITEM_ID_`, `WEAPON_ID_`,
`ARMOR_ID_`, `ACCESSORY_ID_`, `VITAL_ITEM_ID_`.

**Do**

```c
/* Item ids: the index into g_Items. */
enum {
    ITEM_ID_HEALING_HERB = 1,
    /* ... */
};

void Item_Add(u16 item_id, u8 item_count);
```

**Don't**

```c
typedef u16 ItemId;                                        /* a name the compiler never checks */
typedef enum ItemId { ITEM_ID_HEALING_HERB = 1 } ItemId;
void Item_Add(ItemId item, u8 count);                 /* an int where retail passes a u16 */
```

## Evidence

A name needs evidence from a reader, writer, API argument or other source. Record the evidence in
the commit body. A name without evidence stays an address name or `unk_<OFF>`.

The `source` field of a function or global's `config/symbols.toml` row describes what it does or
holds in one short present-tense sentence, using game terms. It does not record callers, addresses,
implementation details or naming evidence. Leave it out when the role is unknown.

A name you invent never holds an 8-digit address (`Menu_SwapBytes3`, `EFFECT_BANK_80140000`); only the tool names `func_<ADDR>`, `D_<ADDR>`, `L<ADDR>`, `jtbl_*`, `jpt_*` and `s_gap_*` do. `tools/check_names.py` enforces this in `include/` and `src/` and lists the legacy offenders in `config/address_names.txt`: rename one and delete its line.

An address name (`func_801D73B4`) spells its address and takes no `@`. Offset and address comments (`/* 0x1C */`, `/* D_80148627 */`) keep their own form.

A count ("3 entries, so party"), an offset match, a type or a tool's output is not evidence.
Community names (bof3-notes, cheat lists) confirm a name the uses already support; they are never
the evidence alone. SDK names are the PsyQ 3.7 declarations.

Name as the original developers did. No symbols survive in the executables (only SDK strings and
the `CAPCOM Mar 26 1998` build stamp), so their words are the disc labels. Order of evidence for a
name: the developer labels, then the retail text and data (the player's words), then the reference
notes, then what the code visibly does. A label whose meaning is unproven stays a tag until its
code shows it. When the larger purpose is unknown, a name for what the code visibly does in game
terms passes (`Actor_Fly`, `Effect_CountDownTimer`). Without even that, keep the address
name or `unk_<OFF>`: a mechanical name is worse than none, because it looks finished.

Names are English. A label in romaji or shorthand becomes the English word it stands for
(`SISYOU` 師匠 is `Master`), and a game concept takes the English the US game text uses, unless
[spelling](naming.md#spelling) lists the project's own word. Data is the retail data: values, tables and
text keep their retail bytes and spelling, whatever the code calls them.

## Types and values

A type is the shape the retail accesses prove, not a shape borrowed from another game. A value is
the meaning a reader, a writer or a table proves, not a number with a likely story.

### Fewest types

One definition per thing, in its owning header; local to an image only when one image uses it. A
second reader moves a type up ([lowest scope wins](layout.md#lowest-scope-wins)). A game type is shared only
when two or more subsystems store the same layout.

| Type                            | Holds                       |
| ------------------------------- | --------------------------- |
| `Point2s`, `Point2u`, `Point2l` | 2-D vectors by member width |
| `Point3s`, `Point3l`            | 3-D vectors by member width |
| `Coord`                         | a 16.16 coordinate          |

The shared fundamentals are defined once in `include/common/vector.h` and `include/common/fixed.h`. Local types with a proven
matching layout use the shared type and member names. PsyQ types stay at SDK calls; PsyQ's padded
`VECTOR`, `SVECTOR`, `DVECTOR`, `CVECTOR` and `RECT` are reused where the pad is real. A record that
holds a position declares the member that matches its access width. `FIELD()` reads become members
when touched.

### Globals are records

Adjacent globals that callers read through one base, step with one stride or clear together are one
struct, array of structs or union, with members named by role. Declare it once in the owning header
([globals](layout.md#globals)). A lone address stays a plain global.

**Do**

```c
extern PartySlot g_Party[PARTY_SLOT_COUNT];   /* one array, one stride */
```

**Don't**

```c
extern u8 g_PartyHp0;                         /* loose globals at one base and stride */
extern u8 g_PartyHp1;
```

### Widths and asserts

`include/types.h` owns the widths (`s8`, `s16`, `s32`, `s64`, `u8`, `u16`, `u32`, `u64`), the
assert macros and `true`/`false`. `include/sys/math.h` owns the fixed-point unit (`ONE`, 4096 =
1.0). Every record in a shared header carries `ASSERT_SIZE(Type, size)` and
`ASSERT_OFFSET(Type, member, offset)` for each proven member. An assert is a compile-time check,
not a comment.

| Concern                                   | Owner                                                                          |
| ----------------------------------------- | ------------------------------------------------------------------------------ |
| widths and assert macros                  | `include/types.h`                                                              |
| packed vectors; fixed-point `Coord`       | `include/common/vector.h`, `include/common/fixed.h`                            |
| generic helpers and masks                 | `include/common/util.h`                                                        |
| fake-match helpers and markers            | `include/match/match.h`                                                        |
| PsyQ declarations and records             | the PsyQ headers (`include/psyq`); game-only additions in `include/psx/psyq.h` |
| game records                              | `include/<subsystem>/`                                                         |
| image-local declarations                  | the image header ([lowest scope wins](layout.md#lowest-scope-wins))            |
| declarations shared by one group's images | the group header                                                               |

### Values

1. Every raw RAM address becomes its symbol. A raw address in `src/` is a lookup failure: search
   `config/symbols.toml`, `include/` and `src/` for `0xADDR` to name the global, constant or
   region macro.
2. A value gets a name only when its evidence gives it one meaning
   ([constants](naming.md#constants-and-macros)). Its role picks `enum` or `#define`:

| The value is                                             | Form                                                                                                                                                                                      |
| -------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A bit of one flag word, set with `\|` or tested with `&` | `typedef enum <Name>Flags { <TAG>_<NAME> = 1 << n, ... } <Name>Flags;`, one enum per flag word, bit 31 as `0x80000000`; a mask with one meaning is a member equal to the `\|` of its bits |
| One of a closed set, compared with `==` or `switch`ed on | `typedef enum <Name> { <TAG>_<NAME> = 0, ... } <Name>;` with explicit values: states, steps, modes, types, commands, results                                                              |
| An id                                                    | the retail fixed-width integer; an anonymous `enum` of its values ([ids](#ids))                                                                                                           |
| A yes/no value: only 0 or 1, tested for truth            | `true` / `false` from `include/types.h`: full-word yes/no returns and locals are `bool` (`s32`); byte-wide yes/no members and returns stay `u8` with `true` / `false`                     |
| A count, size, stride or limit                           | `#define` (it sizes arrays and works in `#if`)                                                                                                                                            |
| A typed value, or one used outside C (asm, linker)       | `#define`                                                                                                                                                                                 |
| A per-image value                                        | `#define` in the image header                                                                                                                                                             |

No struct member has an enum type: an enum-typed member is 4 bytes. A member keeps its width (`u8 mode; /* BattleMode */`, `u16 flags; /* BattlerFlags */`): an `enum`
is an `int` to the retail compiler and would move the layout ([compiler chain](toolchain.md#compiler-chain)). An enum constant is an `int` constant, so
`flags & BATTLER_DAMAGED` compiles as `(1 << 6)` does. A `(1 << n)` value that is only compared,
never combined, is a state and belongs in its closed-set `enum`.

3. No blind bulk replace. Each replacement needs a reader, a writer or a table that proves it.

Group the accesses by base from the retail assembly and the C casts; the type whose members remove
the most casts is the next one to prove.

Constants are grouped by domain: one enum per table or concept (`ITEM_ID_*`, `WEAPON_ID_*`, `ARMOR_ID_*`),
one `#define` run per topic, in the order a reader of that topic expects: ids and flags by value,
offsets in layout order, steps in flow order, a width beside its height. Within one group the
values ascend, and an alias sits next to the value it aliases. Reordering never changes a value,
and the vendor headers under `include/psyq` keep their original text.

**Do**

```c
typedef enum BattlerFlags {
    BATTLER_FLAG_OCCUPIED = 1 << 0,
    BATTLER_FLAG_KO       = 1 << 6,
} BattlerFlags;

#define PARTY_SLOT_COUNT 3

if (battler->state == BATTLER_STATE_IDLE && (battler->flags & BATTLER_FLAG_KO) == 0) {
```

**Don't**

```c
#define BATTLER_KO 0x40                 /* a flag bit outside its flag word's enum */
enum { PARTY_SLOT_COUNT = 3 };          /* a size as an enum: unusable in #if */

if (battler->state == 2 && !(battler->flags & 0x40)) {
```

### How a value is written

Write each number the way its users read it: decimal for quantities, hex for bit patterns and
addresses. The access decides: find the reader in the retail assembly before choosing.

| The users                                                 | Write                                                                                      | Example                             |
| --------------------------------------------------------- | ------------------------------------------------------------------------------------------ | ----------------------------------- |
| test, set or clear bits (`&`, `\|`, `^`, `~`, `<<`, `>>`) | a named flag when the bit has one meaning, else hex                                        | `ITEM_FLAG_VITAL`, `0x80`           |
| byte or halfword mask                                     | `BYTE_MASK`, `HALF_MASK`                                                                   | `id & BYTE_MASK`                    |
| other mask or field extraction                            | named for its field, else hex at the width of the field                                    | `0x0F`                              |
| count, index, loop bound, size in elements, timer         | decimal                                                                                    | `8`, `24`                           |
| coordinate, pixels, speed, HP, damage, price, color value | decimal, signed when negative                                                              | `-4`, `320`, `128`                  |
| byte offset or stride inside a record                     | hex, matching the `/* 0x3C */` member comments; a stride becomes a typed array             | `0x140`                             |
| angle (4096 = one turn)                                   | `ANGLE_<degrees>` when it is a whole number of degrees in the set, else decimal            | `ANGLE_90`, `ANGLE_45`, `341`       |
| "none" or "empty" marker                                  | the named marker (`GAME_NONE`, `FORMATION_SLOT_EMPTY`), else hex at the width of the field | `slot != 0xFF`                      |
| address, encoded multi-bit value                          | hex                                                                                        | `0x8080`                            |
| sound cue                                                 | `EMI_CUE_ID(bank, index)` (`include/audio/cue.h`), never the raw cue id                    | `EMI_CUE_ID(SND_BANK_COMMON, 0x00)` |
| fixed point (4096 = 1.0)                                  | `ONE`, `ONE / 2`, `ONE / 4`, else decimal; shifts by 12 stay literal                       | `ONE / 2`                           |
| pad buttons and other SDK values                          | the PsyQ names; a game set where one exists                                                | `PADLup \| PADLdown`                |
| character or text code                                    | the game's text encoding (`include/game/text.h`), never a bare byte                        | `STRING_END`                        |
| function or data address                                  | the symbol, never a number                                                                 | `func_80196FFC`, `&g_Party`         |
| unused fill or padding                                    | a `pad` or `unk` member, value as stored                                                   | `0xCC`                              |

Fixed point: the 16.16 `Coord` union (`include/common/fixed.h`) is used where code reads or writes
one half, or uses a half together with the whole value (`COORD_INT`, `COORD_FRAC`). Elsewhere the
value is the whole `s32` word, read with `FIX_INT(x)` (integer part) and `FIX_FRAC(x)` (low 16 bits). A 4.12 value is a plain integer, written with `ONE` and
`FIXED_MUL` (`include/sys/math.h`).

A constant compared against an unsigned retail operand keeps its `U` suffix in the `#define`.

Width masks, shifts and arithmetic stay literal. A value that reads both ways takes the form of its
main reader and a comment for the other. A set a `switch` walks becomes an `enum`.

The fixed-point names live in `include/sys/math.h`: `ANGLE_45`, `ANGLE_90`, `ANGLE_180`, `ANGLE_270`
(`ONE` is the full turn), `ONE / 2` and `ONE / 4` for fixed-point halves, and `DEG(d)` for a degree count the code
converts at run time (`DEG(step_degrees)`). An angle and a fixed-point value of the same size keep
their own name: `ANGLE_180` turns, `ONE / 2` scales.

A number with one game meaning in two or more places is one `TAG_UPPER_SNAKE` constant in the
owning header, with a comment that says the unit: `AREA_CAMERA_STEP` (camera turn per frame). The
same number with two meanings is two constants, or stays literal where it is used once. A number
used once stays literal, with a comment when its meaning is not plain.

**Do**

```c
item_id = word & BYTE_MASK;
trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
actor->angle += ANGLE_90;
actor->speed  = ONE / 2;
g_AreaCameraAngle.vx += AREA_CAMERA_STEP;
if (battler->hp < 100) {
```

**Don't**

```c
item_id = word & 255;
trigger = INPUT_REPEATED(held, 0xF000);
actor->angle += 0x400;
actor->speed  = 0x800;
g_AreaCameraAngle.vx += 22;              /* the same step, written again at each use */
if (battler->hp < 0x64) {
```

### How a string is written

A string is `char` or `u8` by its reader, and always a string literal, never hex bytes.

| The reader                                                | Type   | Example                                |
| --------------------------------------------------------- | ------ | -------------------------------------- |
| C library, SDK or disc (format strings, file names, tags) | `char` | `"BASLUS-00422BOF3%02d"`, `"MATH_TBL"` |
| game text (the message and menu fonts)                    | `u8`   | `"Set" T_SP "rod"`                     |

Build game text from the `include/game/text.h` pieces. There is no string typedef. One role name has
one type in every image that declares it. Data that code reads as records is an array of the record
struct, never a `u8` blob with casts.

**Do**

```c
char s_SaveFileFormat[] = "BASLUS-00422BOF3%02d";
u8 g_ItemName[] = "Set" T_SP "rod";
```

**Don't**

```c
u8 s_SaveFileFormat[] = { 0x42, 0x41, 0x53, 0x4C, 0x55, 0x53, 0x2D, 0x30, 0x30, 0x34, 0x32, 0x32 };
```

### Casts become member access

A `*(T *)(base + off)` cast becomes a member access only when the base has a struct whose layout its
other accesses prove.

| Evidence                                               | Result                                         |
| ------------------------------------------------------ | ---------------------------------------------- |
| two or more accesses at fixed offsets, widths agreeing | typed pointer and members                      |
| one access, no other consumer                          | keep the access explicit; report `needs: type` |
| different widths at one offset                         | union of the proven views, or separate views   |
| volatile pointer reread at every access                | typed accessor macro, not a cached local       |

Signedness comes from the load: `lb` makes `s8`, `lbu` makes `u8` (same for `lh`/`lhu`). It goes in
the declaration, never in a cast at each site. A cast that breaks the match stays as
`kept: <reason>`. A missing or wrong shared type is a `needs: type <Type>+0xOFF <width> (<n> sites)`
line for the structure owner, never a local extern, width view or cast in a function file.

### Pointers and arrays

A pointer read or written at fixed offsets is a struct pointer. A stride used with an index is an
array of the element type. A table of addresses is an array of typed function pointers or typed
object pointers, so the link relocations produce the retail addresses; a `u32` array of literal
addresses is not a data definition.

A pointer stays a pointer: never cast an object address or a call result through `u32`/`s32` in
source. The fixed-address seams are the only spellings that may carry a literal address
([seams](matching.md#address-seams)).

**Do**

```c
Character* character = &g_Characters[character_index];

character->hp = character->max_hp;
```

**Don't**

```c
u8* base = (u8*)0x80145F04 + character_index * 0x140;

*(s16*)(base + 0x1C) = *(s16*)(base + 0x1E);
```

### Data tables

A data range is a sequence of real variables, not one blob. Each table is its own variable at its
retail address, typed by its record, named for its job ([tables](naming.md#tables)), with members named by
evidence or `unk_3C`. Records follow the readers: a stride read in a loop is an array of a struct;
parallel reads of the same index are members of one record. Pointers in a table are symbols. A
table whose bytes do not match when split stays as it is, with the reason. The comment above a
table says what it is, who reads it (the reader and its address), what one row is, and its count.

Data is plain C: a typed array of structs, or a 2-D array, with one brace row per record and named
constants for the values. No macro wraps a row. A helper macro is fine where it builds a game object
the designers authored as a unit (an item, a character, an enemy, an ability), or fills padding,
constant members or packed bits that a brace row would make easy to get wrong. Geometry and engine
tables (UV rectangles, offsets, steps, sprite cells), matrices and lists of values stay plain data.

**Do**

```c
/* Screen offset of each party slot, read by Battle_PlaceParty (0x801D2A10). */
ScreenPoint g_BattlePartyOffsets[PARTY_SLOT_COUNT] = {
    { 200, 96 },
    { 232, 120 },
    { 264, 144 },
};
```

**Don't**

```c
u8 D_801E2F7C[] = { 0xC8, 0x00, 0x60, 0x00, 0xE8, 0x00, 0x78, 0x00, 0x08, 0x01, 0x90, 0x00 };
```

### Function tables

A function table is an array of function pointers the game indexes to run one entry. Its element
type is the mechanism (`<Thing>Func`, or `Callback` for `void (*)(void)`), one type per signature.
A struct wrapping the array exists only where a copier assigns the table to a stack local; it takes
the table's job name, not its size.

The index gets an `enum` when a dispatcher or a `switch` walks it, so a row reads by meaning
(`[BATTLE_COMMAND_ATTACK]`). The comment says what the table is, who reads it (function and
address), what the index and one row mean, and the count. Two tables share a type when they hold the
same row. A different count alone never justifies a second type, and two jobs never share a type
because their counts match.

**Do**

```c
/* Battle commands by BattleCommand, run by Battle_DispatchCommand (0x801D3C40). */
BattleCommandFunc g_BattleCommands[BATTLE_COMMAND_COUNT] = {
    [BATTLE_COMMAND_ATTACK] = Battle_RunAttack,
    [BATTLE_COMMAND_DEFEND] = Battle_RunDefend,
};
```

**Don't**

```c
u32 D_801E3000[] = { 0x801D4410, 0x801D4580 };   /* literal addresses do not relocate */
```

## SDK names

PsyQ is linked into every image, so a game name never takes a name the SDK or libc owns. Every
game name is tagged or starts with `g_` or `s_`. The only untagged names are the SDK's own and the
`util.h` helpers that guard a PsyQ spelling (`#ifndef ABS`). Never define `CHAR_BIT`, `CHAR_MAX` or
`CHAR_MIN`.

Game code says what it means through PsyQ's names for SDK calls and values, symbols for RAM and
named registers for hardware. The game was written against the SDK's names, with its own macros for
what it does with them. System tags build on PsyQ names and never copy,
rename or forward them one-to-one.

- Call the SDK and use its names directly: `CdControl(CdlSetloc, ...)`, `SpuSetKey(SPU_ON, ...)`,
  `PADLup`. No layer renames or copies an SDK value.
- Never a raw SDK number: `0xF000` is `PADLup | PADLright | PADLdown | PADLleft`.
- Convenience macros sit on top of the SDK names where the game repeats something: a merged set
  (`INPUT_DIRECTIONAL`), a check (`INPUT_REPEATED`), a role the code proves (confirm, cancel). Each is at
  most two steps from the real thing ([least indirection](#least-indirection)).
- A function that touches hardware uses the named `HW_REF` register (`include/psx/hw.h`), never a
  raw address.
- Retail data keeps its fixed widths (`s16`, `u32`); `int` and `long` never describe retail data.
- A disc or file format has a self-contained header ([format headers](layout.md#format-headers)).

The match wins: a value inside an SDK macro or an SDK-defined initializer stays as the SDK writes
it, and a site where a convenience macro would move the bytes keeps its form with `kept: <reason>`.

**Do**

```c
/* The four directions of the pad. */
#define INPUT_DIRECTIONAL       (PADLup | PADLright | PADLdown | PADLleft)

trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
input   = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown | PADL1 | PADR1));
CdControl(CdlSetloc, (u8*)&loc, NULL);
DrawSync(0);
```

**Don't**

```c
#define PAD_UP          PADLup                 /* a second name for an SDK value */
#define DISC_CMD_SETLOC 0x02                   /* a copy of an SDK value */
#define GFX_DrawSync DrawSync                  /* a second name for an SDK function */

trigger = INPUT_REPEATED(held, 0xF000);
CdControl(2, (u8*)&loc, NULL);
*(volatile u16*)0x1F801C00 = volume;           /* a raw hardware address */
```

## Helpers

Repeated code becomes one helper; a helper is still plain C. Prefer, in order: an existing helper,
a `static inline` function, a macro. Measured inline behavior:
[toolchain](toolchain.md#inline-functions-and-byte-identity).

### Least indirection

A use site is at most two steps from the real thing: a helper may build on one other helper
(`INPUT_REPEATED` on `INPUT_GetRepeatedButtons`, an accessor on `FIELD`), never on a third. A macro or helper
earns its place when it is reused or when its name says something the raw form does not; one that
only renames or forwards goes.

| Keep                                                                                     | Remove                                                                               |
| ---------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| A helper several sites share: `INPUT_REPEATED`, `HAS_STATUS`, `MIN`, `SYS_DISPATCH_BYTE` | A second name for one function or global: `#define BATTLE_AllocEffect func_801E590C` |
| A constant that names a value, even with one user                                        | A macro that forwards another name with the same arguments                           |
| An accessor several sites share while the type is open, named for the role               | An accessor used once that hides a cast: write the member, or `FIELD` at the site    |
| A seam the hardware or a volatile access needs: `HW_REF`, `VOL`                          | A third level: a macro on a macro on a macro                                         |
| A cast view of a global where the bytes need it, with the reason in its comment          | An `#ifndef` default, or a second definition of the same name                        |
| A per-image setting in each image header                                                 | A `#define` nothing uses and that holds no fact                                      |

A `#define` that only aliases a proven name folds into that name: add or fix the name's `config/symbols.toml`
row, rename the definition and declaration to it, then delete the macro. Only a name with no
evidence goes back to the address.

**Do**

```c
/* The repeatable buttons of a pad mask: INPUT_GetRepeatedButtons sees the held keys
 * filtered to the buttons that repeat. */
#define INPUT_REPEATED(pressed, buttons) (INPUT_GetRepeatedButtons((pressed) & (buttons)))

trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
Battle_AllocEffect();
```

**Don't**

```c
#define BATTLE_AllocEffect      func_801E590C          /* a second name for one function */
#define BATTLE_GLOBAL_BYTE_62F3 (*(u8*)&D_801462F3)    /* a width view instead of a typed global */
```

### Game helpers

`include/common/util.h` holds the generic helpers. Use them instead of writing the expression out.

| Helper                                               | Use                                                               |
| ---------------------------------------------------- | ----------------------------------------------------------------- |
| `ARRAY_COUNT(x)`, `ASSERT_OFFSET(type, member, off)` | element count of an array; member offset, checked at compile time |
| `BYTE_MASK`, `HALF_MASK`                             | the low byte or halfword of a value; a mask, never a sentinel     |
| `GAME_NONE`                                          | no slot, index or result in a byte field; compared, never a mask  |
| `BIT(n)`                                             | one bit, a signed `int` like `1 << n`                             |
| `MIN`, `MAX`, `ABS`                                  | arithmetic; `ABS` keeps the PsyQ spelling                         |
| `CLAMP_MIN(value, min)`                              | raise an lvalue to a lower bound in place                         |
| `RANDOM_MASK(mask)`                                  | `rand()` below a power of two                                     |
| `LOB`, `LOBU`, `LOH`, `LOHU`, `HIH`, `LOW`, `LOWU`   | one byte, half or word of an object, in place (an lvalue)         |

`include/sys/math.h` owns `ONE`; `include/common/vector.h` owns the vector types.

**Do**

```c
item_count = MIN(item_count + 1, ITEM_STACK_MAX);
for (i = 0; i < ARRAY_COUNT(g_PartyFieldOrder); i++) {
```

**Don't**

```c
item_count = (item_count + 1 < 99) ? item_count + 1 : 99;
for (i = 0; i < sizeof(g_PartyFieldOrder) / sizeof(g_PartyFieldOrder[0]); i++) {
```

### Helpers and macros

A small operation used 3+ times, or a clone group, becomes a `static inline` function in the owning
header: a getter, setter, `Is`/`Has`/`Can` test, count, find, flag set or clear, clamp, or a
`Party_ForEachMember`-style walk. No function is added to the binary.

Prefer the inline; the match decides. The retail compiler integrates an inline's compiled form, not its text,
so some bodies compile differently from the code in place
([measurements](toolchain.md#inline-functions-and-byte-identity)). Build every member image: when
the inline moves the bytes, the helper is a macro, and the report names the function and what
moved.

| The body                                              | Helper                                                     |
| ----------------------------------------------------- | ---------------------------------------------------------- |
| takes constants, scalars or locals; reads its globals | `static inline`                                            |
| needs a global pointer after a call                   | `static inline` that reads the global itself, else a macro |
| reads a volatile argument more than once              | macro: an inline reads it once                             |
| assigns a parameter the caller sees change            | macro: an inline writes its own copy                       |
| uses a value argument after a branch, loop or join    | statement macro                                            |
| shares a pointer local `p = &GLOBAL` across accesses  | statement macro                                            |
| works on any integer or pointer type                  | macro                                                      |

One operation has one helper. An inline and a macro never do the same job, and the name shows the
form: an inline is a function (`Battle_CanAct`), a macro is `TAG_UPPER_SNAKE` (`BATTLE_CAN_ACT`).
When an inline moves the bytes and becomes a macro, it takes the macro name in the same commit, and
no name is both a `#define` and a declaration.

| Macro                                       | Form                                                                                                                                                                                       |
| ------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Constant or flag                            | An `enum` or `#define` by role ([values](#values))                                                                                                                                         |
| Value (an expression)                       | `TAG_UPPER_SNAKE`, fully parenthesized, no `do`/`while`: `ABS(x)` for `(((x) >= 0) ? (x) : (-(x)))`                                                                                        |
| A recurring game question                   | A value macro named for the question, object first, used where 3+ sites ask it: `HAS_STATUS(battler, STATUS_CONFUSED)`                                                                     |
| One statement (a call, a store)             | The bare expression, used with `;`: `SYS_DISPATCH_BYTE(table, step);`                                                                                                                      |
| Several statements                          | A `static inline` function; a twin body that an inline moves is a `do { ... } while (0)` statement macro, used inside each member's visible definition                                     |
| Several statements, the wrapper moves bytes | A bare statement macro (no `do`/`while`), used only as a member's whole body or at the end of its body, never under an unbraced `if`/`else`; the member declares the locals the macro uses |
| A whole function                            | Only where the bare statement macro also moves bytes: `<TAG>_DEFINE_<NAME>(name, values...)`; the report names the function and what moved                                                 |

The compiler treats a `do { ... } while (0)` scope as a block that can steer register allocation (it
is a benign fake helper), so a statement macro wrapped in one may move bytes. Use that form only
where every use is measured identical; never `if (1) { }` or bare braces.

- Named by what it builds, in `TAG_UPPER_SNAKE`. No leading underscore, no one-letter names.
- Arguments by meaning, in a natural order, wrapped in parentheses; a statement macro is one
  statement.
- A wrong argument count or type fails to compile; it never shifts bytes silently.
- It lives next to the type it builds, at the lowest scope that covers its users.
- A macro never takes code as an argument and holds no externs and no fake helpers.
- A member is never written out in full when a shared form is exact: a body the compiler compiles
  differently as an inline is a reason for the statement macro, not for a copy.
- Near-copy macros (the same body with a different member, step, limit, value or cast) become one
  base macro that takes the differing parts as parameters. A specific macro on top of it is a
  one-line use of the base and exists only when its name says something the game distinguishes.
- Bodies that differ in structure (a compare, the branch order, an extra store) are different
  functions, never one macro with switches.
- A parameter with the same value at every site is folded into the body.

Which form a twin group takes: [shared bodies](../.agents/skills/decomp/references/refactor.md#shared-bodies).

**Do**

```c
/* Whether the party battler can act this turn: alive and awake. */
static inline bool Battle_CanAct(PartyMember* battler) {
    return battler->chr.hp != 0 && !HAS_STATUS(*battler, STATUS_SLEEPING);
}
```

**Don't**

```c
#define CAN_ACT(b) b->chr.hp != 0 && !(b->chr.status & 0x40) /* untagged, unparenthesized, a raw flag */
#define Battle_CanAct(b) ((b)->stats.current_hp != 0)                     /* a macro in a function's name */
#define DO_STEP(body) do { body } while (0)                  /* code as an argument */
```

## Comments

A comment says what, never how, and only where a name or a type cannot
([standard](https://github.com/raulcorreia7/bof3/blob/main/docs/standard.md#comments)). These
decomp-specific cases stay:

- a `FAKE:` note on a fake helper;
- `@bug`;
- legal text and tool directives (`clang-format off`, the `M2CTX` and `PERMUTER` guards);
- failed attempts in `config/attempts.jsonl`, never in source.

| Where                              | Says                                                                                                 |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------- |
| above a type or table              | what it is in the game, units or ranges, when the name cannot say them                               |
| above a shared-header function     | what it does in game terms, one line, when the name does not say it                                  |
| beside a member                    | its offset, then its role when the name does not say it                                              |
| at a fake-match helper             | `/* FAKE: <reason>. */`, the only marker form ([fake-match helpers](matching.md#fake-match-helpers)) |
| at a retail bug kept for the match | `/* @bug <what goes wrong and when>. */`                                                             |
