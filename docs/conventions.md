# Coding conventions

How bof3-decomp code is written. How to match a function: [matching](matching.md). How to build and
inspect: [toolchain](toolchain.md).

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

| Do                                                                    | Don't                                                         |
| --------------------------------------------------------------------- | ------------------------------------------------------------- |
| Tag every name: `SND_PlayCue`, `Battle_ApplyDamage`, `g_BattleActors` | Leave a game name untagged, or write `g_BATTLE_Actors`        |
| `Tag_VerbObject`: `Message_OpenAnswerMenu`                            | Glue the subject to the verb: `MessageSelectAnswerOpenMenu`   |
| Keep the address name above a named definition: `/* func_801F2C04 */` | Lose the `func_`/`D_` name a search from assembly needs       |
| `snake_case` locals, parameters and members: `item_id`, `party_slot`  | Hungarian or camelCase: `pItem`, `nCount`, `itemId`           |
| Name the role: `BattlePanel`, `coord_x`                               | Name the storage: `BattlePanelRecord`, `half_3A`, `ByteView`  |
| Keep the address name until a caller proves the role                  | Guess a name from a count, an offset or a tool's output       |
| Members and typed pointers: `battler->hp`                             | Casts and offsets: `*(s16*)((u8*)p + 0x1C)`                   |
| `enum` for closed sets and flag words; `#define` for sizes and limits | An `enum` type as a member or parameter (it is an `int`)      |
| Decimal quantities, hex bit patterns: `hp < 100`, `flags & 0x80`      | `hp < 0x64`, `flags & 128`                                    |
| Named bits: `INPUT_REPEATED(held, (PADLup \| PADLdown))`              | `INPUT_REPEATED(held, 0x5000)`                                |
| PsyQ functions and names directly; game macros for sets and checks    | Raw SDK numbers, renamed SDK values, raw hardware addresses   |
| Restate decompiler output as structured C with named locals           | Keep `temp_v0`, `var_s1`, `goto loop_1` and pointer math      |
| `BYTE_MASK`, `MIN`, `ARRAY_COUNT` and the other `util.h` helpers      | A local copy of a helper, or a helper that shadows the SDK    |
| A `static inline` helper for a repeated operation                     | A macro where an inline matches the same bytes                |
| Reusable helpers, at most two steps from the real thing               | A `#define` that only renames or forwards, or a chain of them |
| Braces on every body; parentheses around bitwise operands             | `if (x) y();`, `if (a & B && c)`                              |
| `/* FAKE: <reason>. */` beside every fake-match helper                | A bare `register ... asm()`, `__asm__` or `.word` in C        |
| One `extern` in the owning header                                     | `extern` in a `.c`, or a second name for one address          |
| [Header layout](#header-layout): one block per record, in table order | Enums after their users, or an ID enum sorted by name         |
| One-line `/* */` comments that say what a name cannot                 | A comment that restates the name, tells history or evidence   |
| Adjacent globals as one struct, array or union, members by role       | Loose globals at one base or stride                           |

## Language and formatting

C89 plus the extensions the retail compiler supports: designated initializers for data tables and
`static inline` ([compiler](#compiler)). No mixed declarations and code, no declarations in `for`, no `_Bool`, no anonymous
unions, no `//` comments.

The layout: 4-space indent, 120 columns, braces on the same line, `T* x` pointers, declarations and
assignments aligned within each block. The formatter owns it, so never hand-align
([formatter](#formatter)).

A function reads in blocks, like its pseudocode: the declarations, then one block per step (set up,
loop, finish), with one blank line between blocks and none at the start of a block. The order,
the loops and the stop conditions show at a glance. The formatter keeps at most one blank line and
never adds one inside a function, so the blocks are yours to place. Blank lines never change the
bytes.

- Every `if`, `else`, `for`, `while` and `do` body has braces, even one statement.
- A bitwise expression inside a comparison or a logical operator is in parentheses.
- `for` has its init, condition and step; `do`-`while` only when the body must run first; `goto`
  only for a proven shared exit.

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

## Names

### Register

| Thing                                    | Form                        | Example                                  |
| ---------------------------------------- | --------------------------- | ---------------------------------------- |
| system function                          | `TAG_PascalName`            | `SND_PlayCue`, `EMI_LoaderInit`          |
| game function                            | `Tag_PascalName`            | `Battle_ApplyDamage`, `Party_AddItem`    |
| global                                   | `g_` + tag word + name      | `g_BattleActors`, `g_SndVolume`          |
| file static                              | `s_` + tag word + name      | `s_BattleDamageScale`                    |
| type                                     | PascalCase, no tag, no `_t` | `Battler`, `PartyBattler`, `ScreenPoint` |
| constant, enum value, macro              | `TAG_UPPER_SNAKE`           | `BATTLE_ACTOR_MAX`, `SYS_DISPATCH_BYTE`  |
| generic helper (`include/common/util.h`) | untagged capitals           | `ABS`, `MIN`, `CLAMP`, `BYTE_MASK`       |
| local, parameter, member                 | `snake_case`                | `item_id`, `party_slot`, `hp`            |
| SDK, BIOS, hardware                      | unchanged                   | `CdControl`, `PADLup`, `GPU_GP0`         |

Whole words, one spelling per concept across every image. A name is a game or engine name, as a game
programmer of the era would write it: `BattleEffect`, `EncounterTable`, `g_Party`, `timer`. It never
describes storage, offsets, widths or how the thing was found. A member keeps its `_XX` offset suffix
only while its role is unknown.

**Don't**

```c
typedef struct { u8 b; } Word08;         /* a width */
extern PartyRef g_PartyView;             /* how it was found */
#define MAP_TABLE_OFFSET 0x40            /* an offset */
#define SCRATCH_ADDRESS  0x1F800000      /* an address */
```

**Do**

```c
#define PARTY_SLOT_COUNT 3

extern u8  g_PartyCount;
static s16 s_BattleDamageScale;

void Party_AddItem(u16 item_id, u8 item_count);
```

**Don't**

```c
#define PartySlots 3                         /* a constant in PascalCase */

extern u8  g_PARTY_Count;                    /* the tag in capitals inside a global */
static s16 sDamageScale;                     /* no s_, no tag */

void PartyAddItem(u16 itemId, u8 nCount);    /* no tag, camelCase, Hungarian */
```

### Tags

Every function, global, static, constant and macro carries the tag of the system that owns it.
System tags are capitals, as SDL writes them; game tags are words.

| Kind   | Tags                                                                                                                                                            | Global word                                                                         |
| ------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| System | `SYS_ GFX_ SND_ DISC_ EMI_ SAVE_ STRING_ UI_ INPUT_`: engine, platform and I/O                                                                                  | `g_Sys`, `g_Gfx`, `g_Snd`, `g_Disc`, `g_Emi`, `g_Save`, `g_Text`, `g_Ui`, `g_Input` |
| Game   | `Battle_ BMagic_ Boss_ Enemy_ Party_ Char_ PlChar_ Area_ WorldMap_ Actor_ Scene_ Menu_ Shop_ Master_ Fairy_ Fish_ Game_ Message_ Effect_ Item_ Logo_ Resource_` | the tag without `_`: `g_Battle`, `g_WorldMap`                                       |

A constant or macro takes the tag in capitals: `BATTLE_`, `BMAGIC_`, `PLCHAR_`, `WORLDMAP_`,
`SCENE_`. `MATH_` names only the game's own math routines.

`Field`, `World` and `Etc` are not tags. The disc has `BIN/WORLD##/AREA###` and no other map word:
one resident map engine runs every area, and the world map is 11 AREA images whose map-load entry
sets bit 0 of `flag_32`.

| Tag         | Code                                                                      |
| ----------- | ------------------------------------------------------------------------- |
| `Area_`     | The map engine and the area maps: towns, dungeons and the world map alike |
| `WorldMap_` | Code and data only the world-map areas use                                |

A disc folder number is a tag only until the area's game term is proven.

A subject with its own family of functions is a tag: messages, effects, items. A subject that an
existing tag covers takes that tag: a window or panel is `UI_` or `Menu_`, an ability is `Char_`.
A new tag goes into the table above in the same change.

UI parts:

| Part                                                                 | Tag                                                                                   |
| -------------------------------------------------------------------- | ------------------------------------------------------------------------------------- |
| Shared text, fonts, glyphs, windows, frontend state and choice lists | `UI_` (`g_Ui`)                                                                        |
| Message window, area messages and answer menus                       | `Message_`                                                                            |
| Menu panels, cursors, portraits, icons, stat and caption windows     | `Menu_`                                                                               |
| Battle panels, command menu, target cursor and battle numbers        | `Battle_`                                                                             |
| A screen's own UI                                                    | The screen tag: `Shop_`, `Master_`, `Fairy_`, `SAVE_`, or `Menu_` for title and start |
| Numbers, gauges and list rows                                        | The tag of the screen that draws them                                                 |

### Functions

A function name is `Tag_VerbObject`: the tag, an underscore, a verb, then the thing acted on, with
a qualifier last when two functions differ: `Party_AddItem`, `Battle_FindTarget`,
`Message_OpenAnswerMenu`. The subject is the tag, never a word glued to the verb
(`Message_SelectAnswer`). One verb per concept:

| Verb                            | Meaning                                          |
| ------------------------------- | ------------------------------------------------ |
| `Update` / `Draw`               | per-frame logic and rendering                    |
| `Dispatch`                      | calls one entry of a table                       |
| `NextStep` / `SetState`         | advance a step counter; set a state              |
| `Init` / `Reset` / `Exit`       | lifecycle of a system                            |
| `Start` / `End`, `Load`         | begin and finish; read from disc or memory       |
| `Alloc` / `Free`                | take and release a slot                          |
| `Get` / `Set`                   | read and write one value by a known key          |
| `Find`                          | search; returns `GAME_NONE` when nothing matches |
| `Is` / `Has` / `Can`            | yes/no questions                                 |
| `Add`, `Remove`, `Count`        | edit a collection; count its members             |
| `Play`, `Stop`, `Wait`, `Apply` | as the word says                                 |

A function the game calls through a table or a hook takes a plain name for what it does, never a
`Cb`, `Callback` or `Handler` suffix: in PsyQ, `Callback` names the function that registers one. One
function pointer the engine calls at an event is `g_<Tag><Event>Hook`.

**Do**

```c
void Battle_RunAttack(Battler* battler);
u8   Party_FindMember(u8 character_id);   /* GAME_NONE when absent */
```

**Don't**

```c
void Message_OpenAnswerMenu(void);   /* no tag; subject before the verb */
void Battle_AttackCb(Battler* battler);
void Battle_AttackHandler(Battler* battler);
u8   Party_GetMember(u8 character_id);    /* Get never fails; this searches */
```

### Variables, parameters and members

Locals, parameters and members are `snake_case`, with no Hungarian prefixes (`p`, `n`, `i`). The
word says what kind of number it is:

| Word            | Holds                                             | Example                        |
| --------------- | ------------------------------------------------- | ------------------------------ |
| `<thing>_id`    | which thing in the game's data, typed `<Thing>Id` | `item_id`, `character_id`      |
| `<thing>_index` | a position in a runtime array                     | `fairy_index`, `battler_index` |
| `<thing>_slot`  | a position in a fixed container the player sees   | `party_slot`, `save_slot`      |
| `<thing>_count` | how many                                          | `item_count`                   |
| `<thing>_type`  | a category                                        | `ability_type`                 |
| `mode`          | a system's current state                          | `mode`                         |
| `cursor`        | a byte pointer that walks a buffer                | `cursor`                       |

No `kind` and no `class`. A loop counter with no other meaning is `i` or `j`. Parameters put the
thing acted on first.

A member name states the role, never the width or the offset. An unknown member is `unk_3C` with a
`/* 0x3C */` comment; padding is `pad_3C`. Two members that would share a name take a more specific
role (`tint_mode` and `blend_mode`, not `mode_a`). One name per member in every image; a divergence
is open work until the use sites decide the role word.

**Do**

```c
typedef struct Battler {
    /* 0x1C */ s16 hp;      /* 0 on KO */
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ u8  pad_20[4];
    /* 0x24 */ Vec2s coord;
} Battler;

void Fairy_SetJob(u8 fairy_index, u8 job_type);
```

**Don't**

```c
typedef struct Battler {
    s16 half_1C;            /* the width and offset, not the role */
    s16 hp2;                /* a guess with a number */
    u8  data[4];
    Vec2s pos_24;
} Battler;

void Fairy_SetJob(u8 job, u8 idx);   /* the thing acted on last; abbreviated */
```

### Ids

An id is the fixed-width integer the retail data stores, named `<thing>_id`; its values are
constants in an anonymous `enum` whose comment names the table they index. No typedef per id: in C
it checks nothing that `item_id` does not already say, and an `enum` type would change the width
([compiler](#compiler)). Each retail table has its own constants: `ITEM_ID_`, `WEAPON_ID_`,
`ARMOR_ID_`, `ACCESSORY_ID_`, `VITAL_ITEM_ID_`.

**Do**

```c
/* Item ids: the index into g_Items. */
enum {
    ITEM_ID_HEALING_HERB = 1,
    /* ... */
};

void Party_AddItem(u16 item_id, u8 item_count);
```

**Don't**

```c
typedef u16 ItemId;                                        /* a name the compiler never checks */
typedef enum ItemId { ITEM_ID_HEALING_HERB = 1 } ItemId;
void Party_AddItem(ItemId item, u8 count);                 /* an int where retail passes a u16 */
```

### Types

Types are PascalCase with no tag. A game concept that shares a layout gets its own typedef of the
shared type, with its comment, so the meaning stays when the layout is reused.

**Do**

```c
/* A point on the 320x240 screen, in pixels. */
typedef Vec2us ScreenPoint;
```

**Don't**

```c
typedef struct { u16 x; u16 y; } ScreenPointData;   /* a second layout, a filler word */
```

#### Storage words

A name says what a thing is, never how it is stored or found. Drop the storage word; what is left is
usually the name. The same holds for `Ref`, `View`, `Window`, `Row`, `Scratch`, `_ADDRESS` and
`_OFFSET` in a new name.

| The word leaks | Words                                                    | Write instead                                                                                              |
| -------------- | -------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| width          | `Byte`, `Half`, `Word`, `Bytes`, `Words`                 | the role; `unk_<OFF>` until it is known                                                                    |
| shape          | `Record`, `Rec`, `Entry`, `Row`, `Block`, `Chunk`, `Raw` | the thing itself: `BattlePanel`, not `BattlePanelRecord`                                                   |
| a second view  | `View`, `As<Type>`                                       | a union member named by role; a byte or half of one value is `LOBU(x)`, `LOH(x)` (`include/common/util.h`) |
| nothing        | `Data`, `Info`, `Obj`, `Object`, `Work`, `Misc`          | what it holds: `FishingState`, not `Area030Work`                                                           |
| a number       | `Table6`, `Area016`, `Callback3`                         | what the index selects (`g_BattleCommands`); the place or system once proven (`Fishing`, `Town`)           |

| Today                                       | Becomes                                                                             |
| ------------------------------------------- | ----------------------------------------------------------------------------------- |
| `BattlePanelRecord`, `GameStateRecord`      | `BattlePanel`, `GameState`                                                          |
| `BattleActorRecord`, `PartyRow`             | `Battler`, `PartyBattler`                                                           |
| `g_BATTLE_TargetRecord`, cast at every use  | a `BattlePanelTask*` named for whose panel it holds                                 |
| members `flags_12C`, `slot_12D`, `state_01` | the role, offset in the comment: `/* 0x12D */ u8 unk_12D;` until the role is proven |

A storage word stays when it is the game's or the hardware's own term: a save `Slot`, a menu `Row`
the player sees, the PlayStation `Scratchpad`, an SDK name.

### Tables

- A table is the plural of what its index selects, in game terms: `g_Weapons`, `g_AreaEncounters`,
  `g_BattleTurnPhases`, `g_SceneEvents`.
- A sequence is named for what happens: `g_MenuStatusOpen`.
- No `Table`, `List`, `Map`, `Funcs`, `Steps`, `Handlers` or `Callback` word, and no wrapper type.
- The element type carries the mechanism: `<Thing>Func`, one type per signature. The no-argument
  entry `void (*)(void)` is `Callback` (`include/common/handler.h`).
- Until the index is known, a table keeps its address name. Per-image tables of different tasks
  never share a numbered name.

**Do**

```c
typedef void (*BattleCommandFunc)(Battler* battler);

extern Weapon            g_Weapons[WEAPON_COUNT];
extern BattleCommandFunc g_BattleCommands[BATTLE_COMMAND_COUNT];
```

**Don't**

```c
extern u8    g_WeaponsTable[];         /* a Table word, raw bytes */
extern void* g_BattleHandlerTable5[];  /* untyped entries, a number */
```

### Constants and macros

A value gets a name only when a header, the SDK, a string or a table gives it one meaning; one
number may carry two names when two consumers use it differently. A power of two alone does not
prove a flag. Which form a value takes: [values](#values).

Constants, enum values and macros are `TAG_UPPER_SNAKE`. The generic helpers in
`include/common/util.h` stay untagged capitals ([helpers](#game-helpers)).

### SDK and libc names

PsyQ is linked into every image, so a game name never takes a name the SDK or libc owns. Every
game name is tagged or starts with `g_` or `s_`. The only untagged names are the SDK's own and the
`util.h` helpers that guard a PsyQ spelling (`#ifndef ABS`). Never define `CHAR_BIT`, `CHAR_MAX` or
`CHAR_MIN`.

### Game terms

| Thing                 | Name                                                                           |
| --------------------- | ------------------------------------------------------------------------------ |
| Character id          | `character_id` (`CHAR_ID_*`, 11 values with forms)                             |
| Character data        | `Character`, `g_Characters[CHAR_COUNT]`, `g_CharSlot[id]`                      |
| Party order           | `Party_` owns order: `g_PartyFieldOrder`, `g_PartyBattleOrder`, `g_PartyCount` |
| Battle participants   | `Battler`; `PartyBattler`, `EnemyBattler`                                      |
| Enemy definition      | `Enemy` (the BENEMY definition)                                                |
| Script-driven object  | `Actor`, `ACTOR_*`                                                             |
| Field programs        | `PlChar_`                                                                      |
| Battle character bank | `BattlePlayerCharBank`                                                         |

A game object keeps the short noun the disc, the retail text or the reference notes use, without a
system prefix, when the noun means one thing across the game. A system prefix is added only where
two systems have their own thing under one noun. `B` in a disc label marks the battle copy
(`BPLCHAR`, `BENEMY`, `BMAGIC`).

#### Disc words

| Today                                                                                         | Becomes                                                                                                                                                        |
| --------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| "key items"                                                                                   | `VitalItem`, `vital-items`                                                                                                                                     |
| `spell.h`, `SkillClass`, `skill_type`                                                         | `ability.h`, `AbilityType` (`ABILITY_TYPE_HEAL/ASSIST/ATTACK/SKILL`), `Ability.type`                                                                           |
| `monster.h`, Monster                                                                          | `enemy.h`, Enemy                                                                                                                                               |
| Enemy-group `Formation`; `ZoneObject`, `g_AreaZoneList`                                       | `Encounter` (`area-encounters`); `EncounterZone`; Formation is the party formation only                                                                        |
| `ShopObject`, `MasterStatsObject`, `GeneObject`, `ChrysmObject`, `FairyObject`                | `ShopStock`, `MasterStats`, `Gene`, `Chrysm`, `Fairy`                                                                                                          |
| `AreaSceneRecord`, `area-scene`                                                               | `AreaActorDef` (`id`, `clut_select`, `texture_page`, `texture_v`, `texture_mode`, `script_section`), `g_AreaActorDefs`, `area-actor-defs`, `SpriteTextureMode` |
| SHISU, BATE, COMMU00, BATL_END, BATL_OVR, DEMO, FIRST                                         | Status menu, Ability menu, Fairy Village, battle victory, battle defeat, title resources, boot resources                                                       |
| SCENA `Scenario*`, `ScenarioCallback`, `ScenarioElevation`                                    | `Scene*`, `SceneFunc`, `SceneElevation`                                                                                                                        |
| `FieldWork`, `WorldVec`, `WorldCost`, `EmiCueRecord`, `AreaVertexRecord`, `EtcOverlayHead/Id` | `Actor`, `Vec2s`, `AreaCost`, `EmiCue`, `AreaVertex`, `OverlayHeader`/`OverlayId`                                                                              |
| `magic-table`                                                                                 | `bmagic-table`                                                                                                                                                 |
| `BOF3_1.1`                                                                                    | "Breath of Fire III (USA)": volume `BREATH_OF_FIRE3`, 1998-03-26, boot `SLUS_004.22`                                                                           |
| COMMU01-05, BATL_DRA/RE2/RET/SE, AFLDKWA, MTEST, RTEST, A085SE2, A108SE2                      | keep the disc label until code shows the job                                                                                                                   |

| Disc label                  | Game term                      |
| --------------------------- | ------------------------------ |
| `BATTLE`                    | battle program                 |
| `BENEMY`                    | `Enemy`                        |
| `BMAGIC`, `MAGIC#`          | magic (`BMagic_` in battle)    |
| `PLCHAR`, `BPLCHAR`, `PLP*` | character code overlay         |
| `SISYOU` (師匠)             | `Master` menu                  |
| `SHOP`                      | shop program                   |
| `START`                     | start menu                     |
| `GAME` (slot 0 / slot 1)    | engine `game`; `title` screen  |
| `SCENA##`, `SCE##EF*`       | scene controller, scene effect |
| `WORLD##/AREA###`           | area code                      |
| `SLUS_004.22`               | main executable                |
| `LOGO/LOGO.EXE`             | logo player                    |

Archive families (`BGM`, `BENEMY`, `BOSS`, `BMAGIC`, `BPLCHAR`, `PLCHAR`, `ETC`, `SCENARIO`) name
shipped containers, not code folders. Where each disc label lives in the tree: [tree](#tree).

### Evidence

A name needs a cited reader, writer or API argument.

- A function or global carries it in its `config/symbols.toml` row's `source`.
- A member, type or constant carries it in a short comment beside the declaration:
  `/* 0x1C */ s16 hp; /* 'HP' row; 0 on KO */`.
- A name with no evidence stays an address name or `unk_<OFF>`. Each `unk_` name and each header
  alias without a comment is open work.

Write the evidence as `@source: <kind>:<target> [note]`, in a comment beside the thing or in its
row's evidence text. One line, one source; a second source is a second line.

| Kind    | Target                                         | Means                             |
| ------- | ---------------------------------------------- | --------------------------------- |
| `wiki`  | wiki page and anchor, `data/records#area-data` | the wiki documents it             |
| `read`  | `Name@0xADDR` of a function that reads it      | the reader proves the role        |
| `write` | `Name@0xADDR` of a function that writes it     | the writer proves the role        |
| `api`   | the SDK function that takes it                 | an SDK argument types it          |
| `ref`   | a reference project and its note               | a community note confirms the use |

```c
/* @source: read:Battle_RunEvents@0x801DE43C */
/* @source: wiki:data/records#area-data the reward offsets */
```

An address name (`func_801D73B4`) spells its address and takes no `@`. Offset and address comments (`/* 0x1C */`, `/* D_80148627 */`) keep their own form.

A count ("3 entries, so party"), an offset match, a type or a tool's output is not evidence.
Community names (bof3-notes, cheat lists) confirm a name the uses already support; they are never
the evidence alone. SDK names are the PsyQ 3.7 declarations.

Name as the original developers did. No symbols survive in the executables (only SDK strings and
the `CAPCOM Mar 26 1998` build stamp), so their words are the disc labels. Order of evidence for a
name: the developer labels, then the retail text and data (the player's words), then the reference
notes, then what the code visibly does. A label whose meaning is unproven stays a tag until its
code shows it. When the larger purpose is unknown, a name for what the code visibly does in game
terms passes (`Actor_MoveByVelocity`, `Effect_CountDownTimer`). Without even that, keep the address
name or `unk_<OFF>`: a mechanical name is worse than none, because it looks finished.

Names are English. A label in romaji or shorthand becomes the English word it stands for
(`SISYOU` 師匠 is `Master`), and a game concept takes the English the US game text uses, unless
[spelling](#spelling) lists the project's own word. Data is the retail data: values, tables and
text keep their retail bytes and spelling, whatever the code calls them.

### One name

The same name appears in C, Rust, JSON fields, asset types, docs and the status site. An old name is
deleted, not aliased. A `#define NAME func_<ADDR>` alias is debt to fold into the row, not a name.
Every symbol has one declaration ([lowest scope wins](#lowest-scope-wins)); a second name for one
address is a cast macro, not a second `extern`. A rename never deletes a fact: the comment moves
with the name.

### Grep

`git grep -w NAME` finds every use and its evidence, so each fact has one spelling and sits on one
line.

- Write a name in full. Build no name by token pasting (`##`) and split none across lines when the
  match allows it.
- A table row is one line: a `config/symbols.toml` row, a data-table entry, a `@source` line.
- A rename changes every spelling in one commit ([renames](#renames)); no second name stays.
- A base plus offset (`&D_80144952 + 0x16`) hides the symbol at the sum. Name that symbol when the
  bytes still match; keep the sum only where the name changes them.
- A macro that wraps an address name (`ENEMY_COMBATANT`, `BATTLE_ACTIVE_WORK`) hides the name from
  its users. Search the macro name too.

### Spelling

US English in prose and in names, as the US game text spells it: `color`, `behavior`, `center`,
`defense`. The project's own words, used in place of the game text's: `Fairy` (`Fairy`, `FAIRY_*`)
for "Faerie". Retail text keeps its spelling (`ITEM_FAERIE_TIARA`, "Faerie Tiara"). SDK names keep
theirs (`CdlPause`, `SpuSetKey`).

### Renames

A rename is one change: the evidence row, every user in C, Rust, JSON, the docs and the wiki, and
the unit file named for the function, proven byte-exact in every touched image. Search for the
address and the old name as well as the new one ([steps](#rename-steps)).

A named function or global keeps its address name in a one-line comment directly above its
definition and its header declaration, so a search for the address name from assembly, a diff or
old notes still finds it. The rename that names the address writes the line.

```c
/* func_801F2C04 */
MATCH void Message_OpenAnswerMenu(void) {
    WORLD_ARM_ANSWER_MESSAGE_IDLE(2, 4);
}

/* D_80148627 */
extern volatile u8 g_BattlePanelStep;
```

## Types and values

A type is the shape the retail accesses prove, not a shape borrowed from another game. A value is
the meaning a reader, a writer or a table proves, not a number with a likely story.

### Fewest types

One definition per thing, in its owning header; local to an image only when one image uses it. A
second reader moves a type up ([lowest scope wins](#lowest-scope-wins)). A game type is shared only
when two or more subsystems store the same layout.

| Type                       | Holds                       |
| -------------------------- | --------------------------- |
| `Vec2s`, `Vec2us`, `Vec2i` | 2-D vectors by member width |
| `Vec3s`, `Vec3i`           | 3-D vectors by member width |
| `TexRect`                  | a texture rectangle         |
| `Coord`                    | a 16.16 coordinate          |
| `Fixed`, `Fixed12`         | fixed-point values          |
| `Angle`                    | an angle                    |

The shared fundamentals are defined once in `include/common/vector.h`. Local types with a proven
matching layout use the shared type and member names. PsyQ types stay at SDK calls; PsyQ's padded
`VECTOR`, `SVECTOR`, `DVECTOR`, `CVECTOR` and `RECT` are reused where the pad is real. A record that
holds a position declares the member that matches its access width. `FIELD()` reads become members
when touched.

### Globals are records

Adjacent globals that callers read through one base, step with one stride or clear together are one
struct, array of structs or union, with members named by role. Declare it once in the owning header
([globals](#globals)). A lone address stays a plain global.

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

| Concern                                     | Owner                                                                          |
| ------------------------------------------- | ------------------------------------------------------------------------------ |
| widths and assert macros                    | `include/types.h`                                                              |
| packed vectors and fixed-point fundamentals | `include/common/vector.h`                                                      |
| generic helpers and masks                   | `include/common/util.h`                                                        |
| fake-match helpers and markers              | `include/match/match.h`                                                        |
| PsyQ declarations and records               | the PsyQ headers (`include/psyq`); game-only additions in `include/psx/psyq.h` |
| game records                                | `include/<subsystem>/`                                                         |
| image-local declarations                    | the image header ([lowest scope wins](#lowest-scope-wins))                     |
| declarations shared by one group's images   | the group header                                                               |

### Header layout

A name appears before its first use. A header holds, in order: the guard and includes; the
constants and enums several records share; one block per record in table order (its sizes, its ID
`enum` in value order, its struct, its asserts, its `extern`); prototypes in address order. Asserts
follow their struct: `ASSERT_OFFSET` in offset order, then `ASSERT_SIZE`.

```c
#define WEAPON_STRIDE 0x1C

/* Weapon ids: the index into g_Weapons. */
enum {
    WEAPON_ID_DEMONSBANE    = 19,
    WEAPON_ID_HIDDEN_DAGGER = 27,
};

typedef struct Weapon { /* ... */ } Weapon;

ASSERT_OFFSET(Weapon, name, 0x00);
ASSERT_SIZE(Weapon, WEAPON_STRIDE);

/* D_801C8B20 */
extern volatile Weapon g_Weapons[];
```

### Values

1. Every raw RAM address becomes its symbol. A raw address in `src/` is a lookup failure: search
   `config/symbols.toml`, `include/` and `src/` for `0xADDR` to name the global, constant or
   region macro.
2. A value gets a name only when its evidence gives it one meaning
   ([constants](#constants-and-macros)). Its role picks `enum` or `#define`:

| The value is                                             | Form                                                                                                                                                                                      |
| -------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A bit of one flag word, set with `\|` or tested with `&` | `typedef enum <Name>Flags { <TAG>_<NAME> = 1 << n, ... } <Name>Flags;`, one enum per flag word, bit 31 as `0x80000000`; a mask with one meaning is a member equal to the `\|` of its bits |
| One of a closed set, compared with `==` or `switch`ed on | `typedef enum <Name> { <TAG>_<NAME> = 0, ... } <Name>;` with explicit values: states, steps, modes, types, commands, results                                                              |
| An id                                                    | the retail fixed-width integer; an anonymous `enum` of its values ([ids](#ids))                                                                                                           |
| A yes/no value: only 0 or 1, tested for truth            | `true` / `false` from `include/types.h`: full-word yes/no returns and locals are `bool` (`s32`); byte-wide yes/no members and returns stay `u8` with `true` / `false`                     |
| A count, size, stride or limit                           | `#define` (it sizes arrays and works in `#if`)                                                                                                                                            |
| A typed value, or one used outside C (asm, linker)       | `#define`                                                                                                                                                                                 |
| A per-image value                                        | `#define` in the image header                                                                                                                                                             |

A member keeps its width (`u8 mode; /* BattleMode */`, `u16 flags; /* BattlerFlags */`): an `enum`
is an `int` to the retail compiler and would move the layout ([compiler](#compiler)). An enum constant is an `int` constant, so
`flags & BATTLER_DAMAGED` compiles as `(1 << 6)` does. A `(1 << n)` value that is only compared,
never combined, is a state and belongs in its closed-set `enum`.

3. No blind bulk replace. Each replacement needs a reader, a writer or a table that proves it.

Group the accesses by base from the retail assembly and the C casts; the type whose members remove
the most casts is the next one to prove.

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

| The users                                                 | Write                                                                                      | Example                       |
| --------------------------------------------------------- | ------------------------------------------------------------------------------------------ | ----------------------------- |
| test, set or clear bits (`&`, `\|`, `^`, `~`, `<<`, `>>`) | a named flag when the bit has one meaning, else hex                                        | `ITEM_FLAG_VITAL`, `0x80`     |
| byte or halfword mask                                     | `BYTE_MASK`, `HALF_MASK`                                                                   | `id & BYTE_MASK`              |
| other mask or field extraction                            | named for its field, else hex at the width of the field                                    | `0x0F`                        |
| count, index, loop bound, size in elements, timer         | decimal                                                                                    | `8`, `24`                     |
| coordinate, pixels, speed, HP, damage, price, color value | decimal, signed when negative                                                              | `-4`, `320`, `128`            |
| byte offset or stride inside a record                     | hex, matching the `/* 0x3C */` member comments; a stride becomes a typed array             | `0x140`                       |
| angle (4096 = one turn)                                   | `ANGLE_<degrees>` when it is a whole number of degrees in the set, else decimal            | `ANGLE_90`, `ANGLE_45`, `341` |
| "none" or "empty" marker                                  | the named marker (`GAME_NONE`, `FORMATION_SLOT_EMPTY`), else hex at the width of the field | `slot != 0xFF`                |
| address, encoded multi-bit value                          | hex                                                                                        | `0x8080`                      |
| fixed point (4096 = 1.0)                                  | `ONE`, `FIX_HALF`, `FIX_QUARTER`, else decimal; shifts by 12 stay literal                  | `FIX_HALF`                    |
| pad buttons and other SDK values                          | the PsyQ names; a game set where one exists                                                | `PADLup \| PADLdown`          |
| character or text code                                    | the game's text encoding (`include/game/text.h`), never a bare byte                        | `STRING_END`                  |
| function or data address                                  | the symbol, never a number                                                                 | `func_80196FFC`, `&g_Party`   |
| unused fill or padding                                    | a `pad` or `unk` member, value as stored                                                   | `0xCC`                        |

Width masks, shifts and arithmetic stay literal. A value that reads both ways takes the form of its
main reader and a comment for the other. A set a `switch` walks becomes an `enum`.

The fixed-point names live in `include/sys/math.h`: `ANGLE_45`, `ANGLE_90`, `ANGLE_180`, `ANGLE_270`
(`ONE` is the full turn), `FIX_HALF`, `FIX_QUARTER`, and `DEG(d)` for a degree count the code
converts at run time (`DEG(step_degrees)`). An angle and a fixed-point value of the same size keep
their own name: `ANGLE_180` turns, `FIX_HALF` scales.

A number with one game meaning in two or more places is one `TAG_UPPER_SNAKE` constant in the
owning header, with a comment that says the unit: `AREA_CAMERA_STEP` (camera turn per frame). The
same number with two meanings is two constants, or stays literal where it is used once. A number
used once stays literal, with a comment when its meaning is not plain.

**Do**

```c
item_id = word & BYTE_MASK;
trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
actor->angle += ANGLE_90;
actor->speed  = FIX_HALF;
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
([seams](#address-seams)).

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
retail address, typed by its record, named for its job ([tables](#tables)), with members named by
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

Game code says what it means through PsyQ's names for SDK calls and values, symbols for RAM and
named registers for hardware. This is how the game was written: against the SDK's own names, with
the game's own macros for what it does with them. System tags build on PsyQ names and never copy,
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
- A disc or file format has a self-contained header ([format headers](#format-headers)).

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

| Keep                                                                                     | Remove                                                                                          |
| ---------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------- |
| A helper several sites share: `INPUT_REPEATED`, `HAS_STATUS`, `MIN`, `SYS_DISPATCH_BYTE` | A second name for one function or global: `#define BATTLE_AllocEffect func_801E590C`            |
| A constant that names a value, even with one user                                        | A macro that forwards to another with the same arguments: `POS_OFF(x, y)` for `GAME_PAIR(x, y)` |
| An accessor several sites share while the type is open, named for the role               | An accessor used once that hides a cast: write the member, or `FIELD` at the site               |
| A seam the hardware or a volatile access needs: `HW_REF`, `VOL`                          | A third level: a macro on a macro on a macro                                                    |
| A cast view of a global where the bytes need it, with the reason in its comment          | An `#ifndef` default, or a second definition of the same name                                   |
| A per-image setting in each image header                                                 | A `#define` nothing uses and that holds no fact                                                 |

A `#define` that only aliases a proven name folds into that name: add or fix the name's `config/symbols.toml`
row, rename the definition and declaration to it, then delete the macro. Only a name with no
evidence — no row `source` and no fact comment — goes back to the address.

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
#define POS_OFF(x, y)           GAME_PAIR(x, y)        /* forwards with the same arguments */
#define BATTLE_GLOBAL_BYTE_62F3 (*(u8*)&D_801462F3)    /* a width view instead of a typed global */
```

### Game helpers

`include/common/util.h` holds the generic helpers. Use them instead of writing the expression out.

| Helper                                                     | Use                                                              |
| ---------------------------------------------------------- | ---------------------------------------------------------------- |
| `ARRAY_COUNT(x)`, `OFF(type, field)`                       | element count of an array; member offset                         |
| `ALIGN(x, n)`                                              | round up to a power of two                                       |
| `BYTE_MASK`, `HALF_MASK`                                   | the low byte or halfword of a value; a mask, never a sentinel    |
| `GAME_NONE`                                                | no slot, index or result in a byte field; compared, never a mask |
| `BIT(n)`                                                   | one bit, a signed `int` like `1 << n`                            |
| `MIN`, `MAX`, `CLAMP`, `ABS`, `SQ`                         | arithmetic; `ABS` keeps the PsyQ spelling                        |
| `RANDOM_MASK(mask)`                                        | `rand()` below a power of two                                    |
| `LOB`, `LOBU`, `LOH`, `LOHU`, `HIH`, `HIHU`, `LOW`, `LOWU` | one byte, half or word of an object, in place (an lvalue)        |

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
is a benign matching aid), so a statement macro wrapped in one may move bytes. Use that form only
where every use is measured identical; never `if (1) { }` or bare braces.

- Named by what it builds, in `TAG_UPPER_SNAKE`. No leading underscore, no one-letter names.
- Arguments by meaning, in a natural order, wrapped in parentheses; a statement macro is one
  statement.
- A wrong argument count or type fails to compile; it never shifts bytes silently.
- It lives next to the type it builds, at the lowest scope that covers its users.
- A macro never takes code as an argument and holds no externs and no matching aids.
- A member is never written out in full when a shared form is exact: a body the compiler compiles
  differently as an inline is a reason for the statement macro, not for a copy.
- Near-copy macros (the same body with a different member, step, limit, value or cast) become one
  base macro that takes the differing parts as parameters. A specific macro on top of it is a
  one-line use of the base and exists only when its name says something the game distinguishes.
- Bodies that differ in structure (a compare, the branch order, an extra store) are different
  functions, never one macro with switches.
- A parameter with the same value at every site is folded into the body.

Which form a twin group takes: [shared bodies](#shared-bodies).

**Do**

```c
/* Whether the party battler can act this turn: alive and awake. */
static inline bool Battle_CanAct(PartyBattler* battler) {
    return battler->stats.current_hp != 0 && !HAS_STATUS(*battler, STATUS_SLEEPING);
}
```

**Don't**

```c
#define CAN_ACT(b) b->stats.current_hp != 0 && !(b->stats.status & 0x40) /* untagged, unparenthesized, a raw flag */
#define Battle_CanAct(b) ((b)->stats.current_hp != 0)                     /* a macro in a function's name */
#define DO_STEP(body) do { body } while (0)                  /* code as an argument */
```

### Address seams

These are the only spellings that carry a literal address or offset. Each is a seam to replace with
a symbol or a member once the evidence exists.

| Seam                         | Use                                                                         |
| ---------------------------- | --------------------------------------------------------------------------- |
| `MEM(type, addr)`, `MEM_PTR` | a fixed RAM address with no symbol yet                                      |
| `FIELD(type, base, off)`     | one access at an offset of a base whose type is not proven yet              |
| `HW_REF(type, addr)`         | a hardware register (`include/psx/hw.h` names them)                         |
| `SP*`                        | the scratchpad (`include/sys/scratchpad.h`)                                 |
| `VOL(type, x)`               | a volatile access the hardware or a shared buffer needs; not a matching aid |

### Fake-match helpers

Idiomatic C that matches comes first. A fake-match helper is a measured constraint for compiler
behavior C cannot express; `include/match/match.h` defines them and they are inert outside the
matching build. Try in order: correct types and signedness, the original control flow, temporary
lifetimes and declaration order, casts and grouping, the unit's compiler profile, then a helper.

| Group   | Helpers                                                                                                                                                                               |
| ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| benign  | `MATCH_VOLATILE`, `MATCH_VOLATILE_PTR`, `MATCH_FAKE_BARRIER`/`MATCH_BARRIER`, `ORDER_LOCK`, `STACK_PADS` (retail frame bytes nothing explains), `MATCH_FAKE_HOLD`, `NO_SIBLING_CALLS` |
| harmful | `MATCH_FAKE_PIN`/`MATCH_REG` (register pin), `CLOBBER_*`, `MATCH_FAKE_OPAQUE`/`MATCH_FAKE_USE`                                                                                        |

Each use carries an adjacent `/* FAKE: <reason>. */`; a dummy local counts as one, and its note
carries the best pure-C score. Prefer benign over harmful: a pointer local, a
recomputed address or a statement reorder usually moves the allocator before a pin does. A raw
`__asm__`, a bare `register ... asm("reg")` or a `.word` is not source.

## Matching code

Matched C follows every rule on this page; a match is not a reason to keep the decompiler's shape. Restate
the decompiler output as structured C, then add the least constraint the bytes need, with its
reason. Process and diagnosis: [matching](matching.md).

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

**Don't**: decompiler output with a status marker on it.

```c
MATCH void func_8012A4C0(void) {
    u8* temp_v1;
    s32 var_s0;

    var_s0 = 0;
loop_1:
    temp_v1 = (u8*)&D_80145F04 + (*(&D_800F1234 + var_s0) * 0x140);
    *(s16*)(temp_v1 + 0x1C) = *(s16*)(temp_v1 + 0x1E);
    var_s0 += 1;
    if (var_s0 < 3) {
        goto loop_1;
    }
}
```

**Do**: try plain C first (a pointer local, a reorder, the original loop form); when only a helper
matches, use it once, measured, with its reason.

```c
Battler* battler = &g_Battlers[battler_index];   /* the pointer local, not a pin, moves s1 */
/* FAKE: retail rereads the turn counter after the call; pure C best 97.2%. */
MATCH_VOLATILE(s32, turn) = g_BattleTurn;

battler->hp -= damage;
```

**Don't**: unexplained tricks, raw asm, or a pin where a local would do.

```c
s32 dummy;                                 /* no FAKE: note, no measurement */
register Battler* battler asm("s1");       /* a raw pin, not MATCH_REG */

dummy = g_BattleTurn;
if (1) {                                   /* a scope to steer the allocator */
    g_Battlers[battler_index].hp -= damage;
}
__asm__ __volatile__("nop");
```

**Do**: a draft that does not match yet keeps the retail assembly as the build path and records its
score and first mismatch ([markers](matching.md#markers-and-unmatched-bodies)).

```c
#ifdef NON_MATCHING
NON_MATCHING void Party_RestoreHp(void) {
    /* 87.4%; regalloc: v0/v1 swapped in the loop */
    /* ... */
}
#else
INCLUDE_ASM(Party_RestoreHp);
#endif
```

**Don't**: commented-out or `#if 0` bodies, or a draft that replaces the assembly.

```c
#if 0
void Party_RestoreHp(void) { /* ... */ }
#endif
```

## Files and headers

Where source, headers and symbols live. One source tree publishes the matched C and a
byte-identical image, so a path answers which binary and which function a source belongs to.

### Tree

| Path                                                 | Holds                                                                                          |
| ---------------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| `src/engine/<name>/`, `src/engine/<archive>/<slot>/` | code every overlay calls: the executable (`slus`) and `game/00`, which holds the record tables |
| `src/logo/`                                          | the logo player, a separate executable with its own address space                              |
| `src/overlays/<group>/<archive>/<slot>/`             | one overlay image: its disc archive and slot, in the group that loads it                       |
| `src/overlays/<group>/<Name>.h`                      | a body or header shared by images of one group                                                 |
| `src/shared/<Name>.h`                                | a body or header shared by images of several groups                                            |

A shared body sits at the lowest folder that holds every image that includes it: the image folder, then
`overlays/<group>/Name.h`, then `shared/Name.h`.

Groups: `area`, `battle`, `bmagic`, `boss`, `commu`, `menu`, `plchar`, `scenario`, `title`.
Id to path: `emi/<family>/<archive>/<slot>` lives in `src/<root>/<archive>/<slot>`, where `<root>` is
`overlays/<family>` unless the `source_folder` table in `tools/bof3/resolve/ids.py` names another;
`exe/slus_004_22` is `src/engine/slus` and `exe/logo` is `src/logo`.
`config/` and `asm/` follow the id, which is the disc path; `src/` follows what the code does.

The path tells the build which image a source belongs to; the build needs no source list.

### Files

- One function per file until matching is done. The file is named for the function.
- No data or header fold: data and headers are not merged into function files.
- A translation-unit merge happens only where a match needs it. A merge that changes bytes means the
  boundary is wrong: split there.
- An unnamed unit file keeps its offset name (`6FD0.c`) until its functions are known; then it takes
  the topic word ([unit files](#unit-files)).
- The inference splits on a hard fact only: an SDK member object, a different compiler build or a
  different code-generation profile.
- `src/` holds code and data that exist in a retail image, nothing else. A helper with no retail
  address is deleted once a byte-exact build proves no image needs it. A retail function that does
  the same job takes the good name, never an alias.

### Definitions

Each variable is defined exactly once, with its initializer, never in a header. A file lists
`.rodata`, `.data`, `.bss` in address order, then functions.

| Users                 | Name                   | Declaration                      |
| --------------------- | ---------------------- | -------------------------------- |
| this file only        | `static s_<Tag><Name>` | none                             |
| other files or images | `g_<Tag><Name>`        | one `extern` at the lowest scope |
| no evidence yet       | `D_<ADDR>`             | as above, by its users           |

The compiler's own jump tables and literals stay compiler-made. A variable whose section placement
does not match stays in retail assembly with a one-line reason.

### Lowest scope wins

One header per scope: image, group, `include/` topic. A name is defined once, at the lowest scope
that covers all its users:

| Users                       | Declaration                              |
| --------------------------- | ---------------------------------------- |
| one file                    | `static`, or at the top of that `.c`     |
| several files of one image  | the image header (`<archive>_<entry>.h`) |
| several images of one group | the group header (`<group>.h`)           |
| several images              | `include/<subsystem>/*.h`                |

No `extern` in a `.c` file. An image header owns the rest of its image's declarations; a group
header owns what two or more images of that group share; a shared header owns one subsystem domain.
A `.c` includes only the headers for the names it uses.

**Do**

```c
/* battle_03.h */
extern s16 g_BattleDamageScale;

/* Battle_ApplyDamage.c */
#include "battle_03.h"
```

**Don't**

```c
/* Battle_ApplyDamage.c */
extern s16 D_801E5A20;
extern u16 g_BattleDamageScale_u16;   /* a second name for one address */
```

### Format headers

A disc or file format the game defines has one self-contained header: the layout structs with
their asserts, magic values, sizes and flags, and nothing else. It includes only `types.h` and
holds no globals and no functions, so a tool or a test includes it alone; the system that
reads the format includes it. The names match the wiki's format page and the Rust parser.

| Format                                                                                                                                                | Header                   |
| ----------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------ |
| EMI archives, the disc file list, the LZ77 stream, SEP and BGM banks, the BGM selection table, cue tables, overlay headers, script banks              | ours, one per format     |
| STR and XA sector geometry and the XA subheader (`str.h`)                                                                                             | ours: PsyQ leaves it out |
| VAB (`VabHdr`, `ProgAtr`, `VagAtr`), TIM (`TIM_IMAGE`), CD positions and files (`CdlLOC`, `CdlFILTER`, `CdlFILE`), the STR sector header (`StHEADER`) | PsyQ's own type          |

**Do**

```c
/* emi.h: an EMI archive, as stored on the disc. */
#include "types.h"

#define EMI_SECTOR_SIZE 2048

typedef struct EmiEntry {
    /* 0x00 */ u32 size;
    /* 0x04 */ u32 offset;
} EmiEntry;
ASSERT_SIZE(EmiEntry, 0x8);
```

**Don't**

```c
/* emi.h */
#include "types.h"
#include "audio/bank.h"           /* another system */

typedef struct EmiEntry { u32 size; u32 offset; } EmiEntry;

extern u8 g_EmiLoaderState;       /* runtime state in a format header */
void      EMI_LoaderInit(void);   /* code in a format header */
```

### Domains

| Domain                  | Headers                                                                                             | Owns                                                                           |
| ----------------------- | --------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| System: kernel          | `include/sys/{intr,math,sched,scene}.h`                                                             | interrupt callbacks, scheduling, system math routines                          |
| System: tasks           | `include/work/*.h`                                                                                  | task state shared across images                                                |
| System: memory          | `include/sys/scratchpad.h`, `include/psx/mem.h`                                                     | RAM-backed system records, scratchpad views, memory-map access                 |
| System: CD and files    | `include/sys/cd.h`                                                                                  | CD command, file and stream state                                              |
| Graphics                | `include/gfx/*.h`                                                                                   | drawing primitives, VRAM records, graphics state                               |
| Audio                   | `include/audio/*.h`                                                                                 | audio cues, VAB data, audio state                                              |
| Disc and file formats   | `include/sys/{cd_format,emi,lz77,str}.h`, `include/audio/{bank,bgm,cue,sep,vab}.h`                  | one self-contained header per format ([format headers](#format-headers))       |
| Text                    | `include/game/{encoding,text}.h`                                                                    | text encodings, control codes, text records                                    |
| Game records            | `include/game/*.h`                                                                                  | shared database records: items, abilities, characters, enemies, genes, fairies |
| Menu                    | `include/menu/*.h`, `include/sys/gameui.h`                                                          | menu panels, inventory, party selection, saves, shops                          |
| Area                    | `include/area/*.h`, `include/world/*.h`                                                             | area tasks, maps, area data                                                    |
| Battle                  | `include/battle/*.h`                                                                                | battle handlers, actors, work records, battle state                            |
| Scene                   | `include/scenario/*.h`                                                                              | scene steps and effects shared across images                                   |
| Overlay loading         | `include/sys/{emi,exe,loader_tail}.h`, `include/etc/overlay.h`                                      | EMI and executable loading, overlay tables                                     |
| Main executable exports | `include/slus/*.h`                                                                                  | `SLUS_004.22` symbols the overlays read or call                                |
| Platform and matching   | `include/types.h`, `include/common/*.h`, `include/psx/*.h`, `include/psyq/*.h`, `include/match/*.h` | C widths, shared helpers, PSX and PsyQ interfaces, match-only helpers          |

### Include layers

A header in `include/` includes only its own folder and lower layers, so the include graph has no
cycle at file or folder level. A name a higher layer owns is reached through that layer's header
or moves down to the lowest layer that covers its users ([lowest scope wins](#lowest-scope-wins)).

| Layer | Folders and headers                   |
| ----- | ------------------------------------- |
| L0    | `psyq`                                |
| L1    | `types.h`                             |
| L2    | `common/`, `audio`, `psx`, `match`    |
| L3    | `sys`, `gfx`, `area`, `work`, `world` |
| L4    | `common.h`, `etc`, `menu`             |
| L5    | `game`, `scenario`                    |
| L6    | `battle`                              |
| L7    | `slus`                                |
| L8    | `game.h`                              |

`game.h` stays small: the base and the headers every group needs. A group header
(`src/overlays/<group>/<group>.h`, `src/shared/etc.h`, `src/engine/slus/slus.h`) includes `game.h`
and the subsystem headers its images use; an image header includes its group header; a `.c` includes
its image header and nothing else. A subsystem header leaves `game.h` once no group outside the ones
that include it needs it.

### Globals

A global is one `extern` with its real type in the owning header, a name and an address. The address
is a `config/symbols.toml` row, or the name itself for an address name (`D_80145E90`). C and headers keep the address name in a comment as described in [renames](#renames).
Retail RAM address literals stay out of C and headers; hardware registers, the scratchpad range,
BIOS addresses and format offsets stay as defines.

A named global lives in the header of the system that owns it, beside the code that reads and
writes it: `g_SndBgmId` in the sound runtime header, `g_BattleState` in `battle/ram.h`. Each system
header stays self-contained. An executable word with no name yet is declared at the lowest scope that
covers its users ([lowest scope wins](#lowest-scope-wins)); one that several families read is in
`include/slus/data.h` or `include/slus/functions.h`, in address order. The change that names one moves
its `extern` to the owner.

Adjacent globals that form one record are [one struct or array](#globals-are-records).

One name per address per image. A second name for one address (a width or `volatile` view) is a cast
macro, not a second `extern`. A cast macro that names the object itself keeps the bytes
(`#define g_SpadWork ((T *)g_SpadWork)`); an address-taking view hoists the address and changes them.

- `g_SpadWork` is one `extern u8 *g_SpadWork;` in `include/psx/mem.h`. Each mode header views it as
  its work record through a cast macro. An image that reads it as `volatile` defines
  `SPAD_WORK_VOLATILE` before the first include.

#### Order-sensitive macros

Four macros select one declaration, so the `#define` comes before the image's first include. The
header reads the macro when it is first included; a later `#define` changes nothing. Each pair of
declarations has one name and gives a different qualifier or width, so a pair is not a duplicate to
merge, and the macro is not a setting to move into a header.

| Macro                               | Header                  | Selects                                             |
| ----------------------------------- | ----------------------- | --------------------------------------------------- |
| `SPAD_WORK_VOLATILE`                | `include/psx/mem.h`     | `volatile` view of `g_SpadWork`                     |
| `SCRIPT_VARS_VOLATILE`              | `include/game/script.h` | `volatile u8 g_ScriptVars`                          |
| `GRAPHICS_PALETTE_PENDING_VOLATILE` | `include/slus/data.h`   | `volatile u8 g_GfxPalettePending`                   |
| `GAME_SCRATCH_BASE_SCALAR`          | `include/game/spawn.h`  | `u8 D_1F800000[]` in place of the `ScratchPad` view |

### Shared bodies

One original source compiled into several overlays, or one helper called with different arguments,
is written once. An exact twin gets one shared form, chosen by where its members live and what
differs. Find candidates with `bin/coddog cluster <target>` ([coddog](toolchain.md#coddog)); a group is a candidate set, not one body.

| Members                                                                                | Form                                                                                                                                                                                                                                                                                                                    |
| -------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Any, body of one statement                                                             | Not shared: each member writes the statement (`SYS_DISPATCH_BYTE(table, step);`).                                                                                                                                                                                                                                       |
| One image, same body or values used only before the first branch                       | A `static inline` function in the image header; each member is one call (`Battle_ApplyHalfDamage(0x80);`). The inline reads the globals it uses itself and takes values, not pointers it keeps across a call ([inline measurements](toolchain.md#inline-functions-and-byte-identity)).                                  |
| One image, a value used after a branch, loop or join, or a pointer local `p = &GLOBAL` | Each member is a visible definition whose body is one statement macro from the image or group header: `MATCH void func_801EFF8C(void) { g_SpadWork->unk_09 = 0; BMagic_NextStep(); }`. A member's extra statements are written in its own body, never passed to the macro as code.                                      |
| Several images, one member each, same source                                           | One function: one game name in every member's `config/symbols.toml` table, the whole definition (`MATCH`, signature, body) in `src/overlays/<group>/<Name>.h`, included at file level where the function sits. The shared file has no include guard.                                                                    |
| Several images, a value differs per image                                              | As above; the value is a named setting in each member's image header (`#define AREA_SHOP_REQUEST 0x60`).                                                                                                                                                                                                                |
| Several images, one image holds two members                                            | The statement macro for every member of the group, so the body has one source.                                                                                                                                                                                                                                          |
| Several groups, one member each                                                        | One function in the subsystem directory that owns it (`src/shared/Menu_SlidePanelLeft.h`, `src/shared/Actor_FreePaletteFades.h`), not in one user's group. Each member includes it by that path where the function sits (`#include "shared/Menu_SlidePanelLeft.h"`), and the header's first comment lists every member. |
| A helper inside otherwise different functions                                          | A `static inline` function in the group header.                                                                                                                                                                                                                                                                         |

A shared body follows these rules:

- One body lives in `Name.h` at the lowest folder that holds every includer ([tree](#tree)), named
  for the function. Each image keeps a thin `Name.c` that includes the image header, then the body.
- A group is a candidate when its members have equal bytes (exact, or equal after relocations).
  Equal text is not enough.
- One name covers every copy. The same address gives the same `func_<ADDR>`; otherwise a name needs
  evidence in `config/symbols.toml`, one row per image at that image's address. Two evidence names on
  one body stay unshared until one name is chosen. A second copy in one image is `<Name>_<ADDR>` at
  its own address; both definitions stay visible, and each body is the group's statement macro.
- Bodies that differ share a name only as a role: every member fills the same slot (one installer
  or caller, one signature), and the row's `source` names the slot. Otherwise each body takes its own
  name.
- A per-unit compile switch (`SPAD_WORK_VOLATILE`) stays in the thin `.c`, above the image-header
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
back the moment one diverges. The macro forms: [helpers and macros](#helpers-and-macros).

## Comments

A comment says what, never how. It is minimal and high signal: one line, only where a name or a type
cannot carry the meaning. A comment never retells the code, its history, the evidence or the tools.
Evidence for a name goes in the commit body and in the `source` of its `config/symbols.toml` row.
Comments are `/* */` blocks in plain present-tense sentences. Delete a comment that restates a name
or a type.

These stay:

- a `FAKE:` note on a matching aid;
- `@bug`;
- legal text and tool directives (`clang-format off`, the `M2CTX` and `PERMUTER` guards);
- one line above an unfinished `INCLUDE_ASM`: the blocker and the first differing instruction.

| Where                              | Says                                                                                      |
| ---------------------------------- | ----------------------------------------------------------------------------------------- |
| above a type or table              | what it is in the game, units or ranges, when the name cannot say them                    |
| above a shared-header function     | what it does in game terms, one line, when the name does not say it                       |
| beside a member                    | its offset, then its role when the name does not say it                                   |
| at a fake-match helper             | `/* FAKE: <reason>. */`, the only marker form ([fake-match helpers](#fake-match-helpers)) |
| at a retail bug kept for the match | `/* @bug <what goes wrong and when>. */`                                                  |
| above an `INCLUDE_ASM` line        | the blocker and the first differing instruction, one line                                 |

**Do**

```c
/* Add item_count of item_id to the bag; the stack stops at ITEM_STACK_MAX. */
void Party_AddItem(u16 item_id, u8 item_count);

/* @bug reads one row past g_ShopStock when shop_index is SHOP_COUNT. */

/* blocker: effect pointer reload; first diff: lw v0, 0x10(s0). */
INCLUDE_ASM(func_801F1408);
```

**Don't**

```c
/* Adds an item. */                         /* restates the name */
// renamed from func_80123456 in the prefixes change
/* matched at 98% after trying three orders */   /* history and evidence */
/* func_801F30D4 */                         /* restates the INCLUDE_ASM name */
/* TODO fix */
```

## Compiler and tools

The rules above hold whatever the tools are. This section says how the current toolchain applies
them; setup and commands are in [toolchain](toolchain.md).

### Compiler

The retail compiler is GCC 2.7.2 for the PlayStation at `-O2`: C89 with designated initializers and
`static inline`. An `enum` type is an `int`. An inline function is integrated as compiled code, not
as text, and a `do { ... } while (0)` scope is a block that can steer register allocation; which
bodies keep their bytes is measured in
[inline functions and byte identity](toolchain.md#inline-functions-and-byte-identity).

### Formatter

`.clang-format` (LLVM base) holds the layout. `format` applies it; `format-check` fails on any
drift. Declaration order follows [header layout](#header-layout) and is kept by review.

### Unit files

splat names an unnamed unit by its uppercase hex offset. When its functions are known, one
`git mv` renames it, in one commit with every row that names the file (`splat.yaml`). The source folder of a target is what
`source_folder` in `tools/bof3/resolve/ids.py` returns.

### Rename steps

`tools/symbol.py rename` adds the symbol's `config/symbols.toml` row with its `source`, rewrites every
tracked user (definition, prototypes, uses, `config/`), keeps the address name in a comment and moves
the unit file. Then prove every touched image with `check-<image>`:

```sh
tools/symbol.py rename func_<ADDR> <Name> --image <target> --local --source "<evidence>" --dry-run
tools/symbol.py rename func_<ADDR> <Name> --image <target> --local --source "<evidence>"
tools/symbol.py params <Name> old=new ...     # parameter names: definition and prototypes
```

An address name is unique only per image: `--local` limits the rename to that image's `src/` and
`config/` folders, and `--scope PATH...` names the folders. The resident images
(`exe/slus_004_22`, `emi/etc/game/00`) rename with no scope. `tools/symbol.py add` writes a row
without a rename, and `tools/symbol.py refs` ranks the units to name first.

### Symbols and the link

A global's address is its row in `config/symbols.toml`, or the name itself for an address name
(`D_80145E90`). `g_SpadWork` is one row in the `["exe/slus_004_22"]` table. The row is the whole
edit: the link finds the address by itself, with no per-image list to extend and no reconfigure.

```toml
["exe/slus_004_22"]
g_SpadWork = { addr = 0x1F800000, type = "SpadWork", size = 0x400, source = "..." }
```

Rows are written in address order. Keys: `addr`; `type` and `size` for splat; `source` (the evidence);
`alias = true` for a name only the link reads (an SDK data name, a `_nv` view, a name inside
another row), which splat never sees. Rows that overlap fail unless one of the two is an alias.
The generator (`tools/bof3/link/symbols.py`) fails with the row and the fix for an unknown key, a
bad address or an overlap.

An image links with splat's `linker.ld` and its auto files. For each name the objects leave
undefined, `tools/link_symbols.py` adds `PROVIDE(NAME = 0xADDR);` from the table: an address name
spells its own address; a readable name resolves in the rows the image sees, which are its own
table, the resident images that `config/link.toml` lists in `visible_to`, and the owners its
`splat.yaml` names. `exe/logo` is a separate address space and sees only its own table. PROVIDE
defines a name only when nothing else does. For each row of the image's own table that the
image's objects define, `link_symbols.py` also adds `ASSERT(NAME == 0xADDR, ...)`: the linker
proves the row against the address the image gave the symbol. A wrong row fails the link of that
image, and the failure names the row, the address it says, and the address the image links.

A name that cannot be resolved for certain fails the link and names the fix:

| Failure                                                    | Fix                                                                                            |
| ---------------------------------------------------------- | ---------------------------------------------------------------------------------------------- |
| `NAME ... has no address`                                  | add `NAME = { addr = 0x... }` to the failing image's table, or the resident image that owns it |
| `NAME ... has N addresses visible to <target>`             | rename one row so each name has one address in that image                                      |
| `the name spells 0x... but ... gives 0x...`                | fix the row's address or rename it                                                             |
| `NAME: the row says 0x... but the image links it at 0x...` | fix the row's address, or the source that moved the symbol                                     |

- Boss and `battle/15` images read `["emi/battle/battle/03"]` through `symbol_owners` in their
  `splat.yaml`, so battle/03's readable names resolve there.
