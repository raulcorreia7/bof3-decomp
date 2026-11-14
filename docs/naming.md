# Names

How a function, global, static, constant, macro, type, local, parameter or member is named, in the
game's words. A name needs evidence ([conventions: evidence](conventions.md#evidence)); a thing
with no fact keeps its address name (`func_<ADDR>`, `D_<ADDR>`, `unk_<OFF>`).

## Register

| Thing                                    | Form                        | Example                                  |
| ---------------------------------------- | --------------------------- | ---------------------------------------- |
| system function                          | `TAG_PascalName`            | `SND_PlayCue`, `EMI_Init`                |
| game function                            | `Tag_PascalName`            | `Battle_ApplyDamage`, `Item_Add`         |
| global                                   | `g_` + tag word + name      | `g_BattleActors`, `g_SndVolume`          |
| file static                              | `s_` + tag word + name      | `s_BattleDamageScale`                    |
| type                                     | PascalCase, no tag, no `_t` | `Battler`, `PartyMember`, `ScreenPoint`  |
| constant, enum value, macro              | `TAG_UPPER_SNAKE`           | `BATTLE_ACTOR_MAX`, `SYS_DISPATCH_BYTE`  |
| generic helper (`include/common/util.h`) | untagged capitals           | `ABS`, `MIN`, `ARRAY_COUNT`, `BYTE_MASK` |
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

void Item_Add(u16 item_id, u8 item_count);
```

**Don't**

```c
#define PartySlots 3                         /* a constant in PascalCase */

extern u8  g_PARTY_Count;                    /* the tag in capitals inside a global */
static s16 sDamageScale;                     /* no s_, no tag */

void PartyAddItem(u16 itemId, u8 nCount);    /* no tag, camelCase, Hungarian */
```

## Tags

Every function, global, static, constant and macro carries the tag of the system that owns it.
System tags are capitals, as SDL writes them; game tags are words.

| Kind   | Tags                                                                                                                                                                                                                | Global word                                                                         |
| ------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| System | `SYS_ GFX_ SND_ DISC_ EMI_ SAVE_ STRING_ UI_ INPUT_ MATH_ LZ77_`: engine, platform and I/O                                                                                                                          | `g_Sys`, `g_Gfx`, `g_Snd`, `g_Disc`, `g_Emi`, `g_Save`, `g_Text`, `g_Ui`, `g_Input` |
| Game   | `Battle_ BMagic_ Boss_ Enemy_ Party_ Char_ PlChar_ Area_ WorldMap_ Actor_ Scene_ Menu_ Shop_ Master_ Fairy_ FairyCasino_ FairyNickname_ FairyCopyShop_ Well_ Fishing_ Game_ Message_ Effect_ Item_ Logo_ Resource_` | the tag without `_`: `g_Battle`, `g_WorldMap`                                       |

A constant or macro takes the tag in capitals: `BATTLE_`, `BMAGIC_`, `PLCHAR_`, `WORLDMAP_`,
`SCENE_`, `FISHING_`. `MATH_` names only the game's own math routines; `LZ77_` names the decoder.

`Field`, `World` and `Etc` are not tags. The disc has `BIN/WORLD##/AREA###` and no other map word:
one resident map engine runs every area, and the world map is 11 AREA images whose map-load entry
sets bit 0 of `flag_32`.

| Tag              | Code                                                                      |
| ---------------- | ------------------------------------------------------------------------- |
| `Area_`          | The map engine and the area maps: towns, dungeons and the world map alike |
| `WorldMap_`      | Code and data only the world-map areas use                                |
| `Char_`          | Character records, stats and ids                                          |
| `PlChar_`        | The player-character overlay; the disc label is `PLCHAR`                  |
| `Fishing_`       | The fishing pond and its shop                                             |
| `FairyCasino_`   | The casino scene in the fairy village                                     |
| `FairyNickname_` | The nickname scene in the fairy village                                   |
| `FairyCopyShop_` | The copy shop scene in the fairy village                                  |
| `Well_`          | The well minigame                                                         |

`World_`, `PAD_`, `Mem_`, `Matrix_`, `Data`, `Info` and `Work` are not tags. The world-map code is
`WorldMap_`, the pad wrapper is `INPUT_`, the memory helper is `SYS_` and the matrix helpers are
`MATH_`. `World01_` and `WORLD00_` are disc and area labels, not tags.

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

## Vocabulary

One word per concept. A new name uses the `Word`; `Rejected` lists the words that name the same
concept. Two words stay only where the definitions differ. A word the SDK, the hardware or one of the
game's own records owns keeps its meaning (`Callback`, `Bank`, `Slot`, `Cell`); the game never renames it.

| Concept                       | Word                                        | Definition                                                                              | Rejected                                                                               |
| ----------------------------- | ------------------------------------------- | --------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------- |
| Data table                    | the element plural                          | An indexed sequence in memory, named for the plural of what its index selects           | `Table`, `Array`, `Set`, `Pool`, `Funcs`, `Steps`, `Handlers`; `List` for a data table |
| Sound bank                    | `Bank`                                      | A VAB loaded into one SPU bank slot                                                     | —                                                                                      |
| Buffer                        | `Buffer`                                    | A byte region that data passes through                                                  | `Buf`                                                                                  |
| Queue                         | `Queue`                                     | A first-in first-out list of requests                                                   | —                                                                                      |
| Index                         | `Index`                                     | A position in a runtime array                                                           | `Idx`                                                                                  |
| Id                            | `Id`                                        | The value the retail data stores to identify a thing                                    | —                                                                                      |
| Slot                          | `Slot`                                      | A filled position in a fixed container the player sees                                  | —                                                                                      |
| Count and value               | `Count`, `Value`                            | How many elements a collection holds; a generic number whose role the type names        | `Cnt`, `Num`, `Amount`, `Quantity`                                                     |
| Size                          | `Size`                                      | Bytes of storage a record, buffer or primitive takes                                    | `Len` for bytes                                                                        |
| Length                        | `Length`                                    | The number of elements or characters in a run                                           | `Len`                                                                                  |
| Max and limit                 | `Max`, `Limit`                              | The largest value of a quantity; a bound one operation stays within                     | —                                                                                      |
| Function-pointer element      | `<Thing>Func`                               | A function pointer stored in a table, typed for one signature                           | `Handler`, `Proc`, `Routine`, `Fn`, `Cb`                                               |
| Callback type                 | `Callback`                                  | The no-argument `void (*)(void)` entry                                                  | —                                                                                      |
| Scheduler thread              | `Thread`                                    | One cooperative task the main loop runs each frame                                      | `CallbackSlot`, `Callback` for the slot                                                |
| Event hook                    | `Hook`                                      | A function pointer the engine calls at one event                                        | `Callback` for the pointer                                                             |
| State phase                   | `Mode`, `Step`                              | The phase a mode byte selects; the index a state machine advances                       | `Kind` for either                                                                      |
| Dispatch                      | `Dispatch`                                  | Call one entry of a table by index                                                      | `Handle`                                                                               |
| Initialize                    | `Init`                                      | Bring a system or record to ready for first use                                         | `Setup`, `Create`, `New` as a lifecycle verb                                           |
| Start and begin               | `Start`, `Begin`                            | Begin an ongoing operation; enter a discrete script or record                           | —                                                                                      |
| End                           | `End`                                       | Finish a phase or record                                                                | `Finish`                                                                               |
| Stop, exit, close             | `Stop`, `Exit`, `Close`                     | Stop a playback; leave a system; close a window                                         | —                                                                                      |
| Free, release, remove         | `Free`, `Release`, `Remove`                 | Release a slot; give up a claim; take an element out of a collection                    | `Delete`, `Destroy`, `Kill`                                                            |
| Reset and clear               | `Reset`, `Clear`                            | Restart a system; zero one record's fields                                              | —                                                                                      |
| Open                          | `Open`                                      | Open a player-visible window, panel or shop                                             | —                                                                                      |
| Update, tick, run             | `Update`, `Tick`, `Run`                     | Run a frame; advance a countdown; execute one named action                              | `Exec`, `Process`, `Do`, `Handle` for a frame                                          |
| Read and load                 | `Read`, `Load`                              | Transfer bytes from the device; bring a resource into memory                            | `Fetch`                                                                                |
| Get and find                  | `Get`, `Find`                               | Read one known value; search and return `GAME_NONE`                                     | `Lookup`, `Search` as a verb                                                           |
| Set, write and save           | `Set`, `Write`, `Save`                      | Write one value by key; write a record back; write the memory card                      | `Store`, `Put`                                                                         |
| Yes/no questions              | `Is`, `Has`, `Can`, `Test`                  | A property, a possession, an ability, a flag                                            | `Check`                                                                                |
| Create, alloc, spawn, add     | `Create`, `Alloc`, `Spawn`, `Add`           | Construct an object; claim a slot; place it in the world; append an element             | `Make`, `New` as a creation verb, `Append`, `Insert`                                   |
| Type                          | `Type`                                      | The category a retail value selects                                                     | `Kind`, `Class`                                                                        |
| Flag and flags                | `Flag`, `Flags`                             | One bit; a word of packed bits                                                          | `Bits`                                                                                 |
| Mask                          | `Mask`                                      | A bit pattern that selects bits                                                         | —                                                                                      |
| Timer, counter, frame         | `Timer`, `Counter`, `Frame`                 | A countdown; a count of events; a count of rendered frames                              | `Tick` as a noun for the value                                                         |
| Wait and delay                | `Wait`, `Delay`                             | Hold until a condition; a count of frames before an action                              | —                                                                                      |
| Draw, show, display           | `Draw`, `Show`, `Display`                   | Queue primitives; make a message visible; the hardware display buffer                   | `Render`                                                                               |
| Character and char            | `Character`, `Char`                         | The record and its id; the function and constant tag                                    | `Chara`                                                                                |
| Party, party member, player   | `Party`, `PartyMember`, `Player`            | The group; one member record; a playback object                                         | `Member` for a party member                                                            |
| Enemy and boss                | `Enemy`, `Boss`                             | The BENEMY definition and its battle row; a boss battle module                          | `Monster`                                                                              |
| Message, text and string      | `Message`, `Text`, `String`                 | A message request or window; game text content; a byte sequence                         | `Msg`                                                                                  |
| Anim, animation, motion       | `Anim`, `Animation`, `Motion`               | The actor's animation stream; a frame sequence; physical movement                       | —                                                                                      |
| Effect, magic, ability, skill | `Effect`, `Magic`, `Ability`, `Skill`       | A visual effect; the battle magic program; the ability record; an ability of type SKILL | `Fx`, `Spell`                                                                          |
| Item                          | `Item`                                      | The item records and their ids                                                          | `Goods`                                                                                |
| Area, map, scene, field       | `Area`, `Map`, `Scene`, `Field`             | The level; its grid data; what the scene window runs; the field state                   | —                                                                                      |
| World map                     | `WorldMap`                                  | Code and data only the world-map areas use                                              | `World` in a code name                                                                 |
| Position and geometry         | `Pos`, `Point`, `Coord`, `Vector`, `Offset` | A position value; a point type; a fixed-point coordinate; a math vector; a displacement | —                                                                                      |
| Color, tint, RGB              | `Color`, `Tint`, `RGB`                      | A colour value; a colour delta; the packed pixel format                                 | `Colour`                                                                               |
| Abbreviations                 | the full word                               | A name says the thing, not a saved keystroke                                            | `Ptr`, `Buf`, `Tmp`, `Cur`, `Num`, `Idx`, `Cnt`, `Obj`, `Ctrl`, `Mgr`, `Spr`           |

## Functions

A function name takes one of two orders:

1. **Verb first**, the default: `Tag_VerbObject`. The tag, an underscore, a verb, then the thing
   acted on: `Party_AddMember`, `Battle_FindTarget`, `Shop_Buy`.
2. **Object first**, for a family: `Tag_ObjectVerb`. When three or more functions under one tag act
   on the same object, the object comes first, so the family sorts together, as PsyQ writes
   `SsSeqOpen`, `SsSeqPlay` and `SsSeqClose`: `Message_WindowOpen`, `Message_WindowClose`,
   `Message_WindowDraw`.

Count the family across the whole tree. Two functions are not a family. When a third member gets a
name, rename the other two in the same change. A qualifier goes last when two functions differ
(`Battle_TargetNext`, `Battle_TargetPrev`). The subject is the tag, never a word glued to the verb
(`Message_SelectAnswer`). One verb per concept:

| Verb                            | Meaning                                                  |
| ------------------------------- | -------------------------------------------------------- |
| `Update` / `Draw`               | per-frame logic and rendering                            |
| `Tick`                          | advance a countdown timer                                |
| `Run`                           | execute one named action or task                         |
| `Dispatch`                      | call one entry of a table                                |
| `NextStep` / `SetState`         | advance a step counter; set a state                      |
| `Init` / `Reset` / `Exit`       | lifecycle of a system                                    |
| `Start` / `End`                 | begin and finish an ongoing operation                    |
| `Begin` / `End`                 | enter and finish a discrete script or record             |
| `Open` / `Close`                | open and close a player-visible window                   |
| `Load` / `Read`                 | bring a resource into memory; read bytes from disc or CD |
| `Alloc` / `Free`                | take and release a slot                                  |
| `Release`                       | give up a claimed target or actor                        |
| `Get` / `Set`                   | read and write one value by a known key                  |
| `Write` / `Save`                | write a record back; write the memory card               |
| `Find`                          | search; returns `GAME_NONE` when nothing matches         |
| `Is` / `Has` / `Can` / `Test`   | yes/no questions; test a flag                            |
| `Add`, `Remove`, `Count`        | edit a collection; count its members                     |
| `Create` / `Spawn`              | construct an object; place it in the world               |
| `Play`, `Stop`, `Wait`, `Apply` | as the word says                                         |

A function the game calls through a table or a hook takes a plain name for what it does, never a
`Cb`, `Callback` or `Handler` suffix: in PsyQ, `Callback` names the function that registers one. One
function pointer the engine calls at an event is `g_<Tag><Event>Hook`.

**Do**

```c
void Battle_RunAttack(Battler* battler);
u8   Party_FindMember(u8 character_id);   /* GAME_NONE when absent */
void Message_WindowOpen(u8 window_id);    /* one of the Message_Window family */
s32  Message_WindowIsOpen(u8 window_id);
```

**Don't**

```c
void Message_OpenAnswerMenu(void);   /* no tag; subject before the verb */
void Message_OpenWindow(u8 window_id); /* a family member in verb-first order */
void Battle_AttackCb(Battler* battler);
void Battle_AttackHandler(Battler* battler);
u8   Party_GetMember(u8 character_id);    /* Get never fails; this searches */
```

The name test, for every name: it says what the thing is for in the game, what the player or the
engine sees; it has at most three words after the tag (`Effect_FollowTarget`, not
`Effect_CopyBattlerCoordsSetTimers`); its word order follows the two orders above; it has no `And`
and no step list; it has no storage words (no field names, offsets, flag numbers or widths); a
colleague could guess it before reading the body (`Item_Add`, `Battle_EndTurn`, `Shop_Buy`).

## Variables, parameters and members

Locals, parameters and members are `snake_case`, with no Hungarian prefixes (`p`, `n`, `i`). The
word says what kind of number it is:

| Word            | Holds                                                          | Example                        |
| --------------- | -------------------------------------------------------------- | ------------------------------ |
| `<thing>_id`    | which thing in the game's data; the retail fixed-width integer | `item_id`, `character_id`      |
| `<thing>_index` | a position in a runtime array                                  | `fairy_index`, `battler_index` |
| `<thing>_slot`  | a position in a fixed container the player sees                | `party_slot`, `save_slot`      |
| `<thing>_count` | how many                                                       | `item_count`                   |
| `<thing>_type`  | a category                                                     | `ability_type`                 |
| `mode`          | a system's current state                                       | `mode`                         |
| `cursor`        | a byte pointer that walks a buffer                             | `cursor`                       |

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
    /* 0x24 */ Point2s coord;
} Battler;

void Fairy_SetJob(u8 fairy_index, u8 job_type);
```

**Don't**

```c
typedef struct Battler {
    s16 half_1C;            /* the width and offset, not the role */
    s16 hp2;                /* a guess with a number */
    u8  data[4];
    Point2s pos_24;
} Battler;

void Fairy_SetJob(u8 job, u8 idx);   /* the thing acted on last; abbreviated */
```

## Globals, arrays, structs and unions

Name each one for what the game keeps in it, in the words its programmer would use:

| Thing                 | Form                                                     | Example                                     |
| --------------------- | -------------------------------------------------------- | ------------------------------------------- |
| one value             | `g_<Tag><Thing>`, singular                               | `g_ShopSelectedItem`, `g_PartyCount`        |
| a system's state      | `g_<Tag>State`, one per system, typed `<Tag>State`       | `g_ShopState`                               |
| an array              | the plural of one element, sized by its `_COUNT`         | `g_Weapons[WEAPON_COUNT]`, `g_PartyMembers` |
| parallel arrays       | the shared noun, then what each holds                    | `g_InventoryIds`, `g_InventoryCounts`       |
| a struct              | the game noun, singular                                  | `Battler`, `ShopStock`, `EncounterTable`    |
| a struct inside one   | the member named for its role                            | `stats`, `coord`, `cursor`                  |
| a union               | the value, with one member per role it plays             | `argument`: `item_id` or `ability_id`       |
| a pointer to a record | the record's own noun                                    | `Battler* battler = &g_Battlers[i];`        |
| a yes/no local        | the state word                                           | `found`, `done`, `visible`                  |
| a counter             | `timer` counts down to zero; `frame` counts up from zero | `timer`, `frame`                            |

Locals use short game words: `battler`, `item`, `price`, `page`, `cursor`, `count`. A temporary that
matching forces keeps the name of the value it holds.

**Do**

```c
extern Battler   g_Battlers[BATTLER_COUNT];
extern ShopState g_ShopState;

Battler* battler = &g_Battlers[battler_index];
```

**Don't**

```c
extern u8 g_ShopSelectStep;              /* a step of the code, not the item */
extern u8 g_ShopVars[0x40];               /* a filler word, raw bytes */

Battler* ptr = &g_Battlers[i];            /* a storage word for a game object */
s32 tmp2, val;                            /* names that say nothing */
```

### Nested members

A large record groups a run of members that has one meaning. Each group needs evidence: the code
reads the members together, copies them as a unit, or a shared type already names them.

**Do**

```c
typedef struct BattlePosition { Coord x; Coord y; Coord z; } BattlePosition;  /* a point */
typedef struct PartyMember {
    u8 flags, mode, step;       /* the task header */
    BattlePosition pos;         /* copied whole by Effect_CopyBattlerCoords */
    union { u8 byte[4]; u32 word; } cell;  /* only when two readers see the same bytes in two roles */
} PartyMember;
```

**Don't**

```c
struct { s32 a, b, c; } group;  /* nested to look tidy: no reader uses the three together */
Coord z;                        /* a member named z whose role is a frame counter */
```

## Types

Types are PascalCase with no tag. A game concept that shares a layout gets its own typedef of the
shared type, with its comment, so the meaning stays when the layout is reused.

**Do**

```c
/* A point on the 320x240 screen, in pixels. */
typedef Point2u ScreenPoint;
```

**Don't**

```c
typedef struct { u16 x; u16 y; } ScreenPointData;   /* a second layout, a filler word */
```

A role that recurs gets one typedef over the shared block (`Point2s`, `Point3l`, `Coord3D`, `SVECTOR`,
...), in the header that owns its domain, and every member, parameter and global of that role uses it
(`WorldPos`, `SpriteScale`, `CameraAngle`). A one-off keeps the block type and carries the role in its
member name. Never one typedef per member, never a second layout.

### Storage words

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
| a category     | `Kind`, `Class`                                          | `Type`: `BattleOwnerType`, not `BattleOwnerKind`                                                           |
| a saved key    | `Ptr`, `Buf`, `Tmp`, `Cur`, `Num`, `Idx`, `Cnt`, `Obj`   | the word: `index`, `count`, `buffer`, `current`, the thing a pointer names                                 |
| a callable     | `Handler`, `Proc`, `Routine`, `Cb`                       | the action the function runs; `Func` for a table element, `Callback` for `void (*)(void)`                  |

A storage word stays when it is the game's or the hardware's own term: a save `Slot`, a menu `Row`
the player sees, the PlayStation `Scratchpad`, an SDK name.

## Tables

- A table is the plural of what its index selects, in game terms: `g_Weapons`, `g_AreaEncounters`,
  `g_BattleTurnPhases`, `g_SceneEvents`.
- A sequence is named for what happens: `g_MenuStatusOpen`.
- No `Table`, `Array`, `Set`, `Pool`, `Funcs`, `Steps`, `Handlers` or `Callback` word for a data
  table, and no wrapper type. A player-visible menu list keeps `List`; a map's grid data keeps
  `Map` (`MapCell`, `AreaMapBundle`).
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

## Constants and macros

A value gets a name only when a header, the SDK, a string or a table gives it one meaning; one
number may carry two names when two consumers use it differently. A power of two alone does not
prove a flag. Which form a value takes: [values](conventions.md#values).

Constants, enum values and macros are `TAG_UPPER_SNAKE`. The generic helpers in
`include/common/util.h` stay untagged capitals ([helpers](conventions.md#game-helpers)).

## Game terms

| Thing                 | Name                                                                           |
| --------------------- | ------------------------------------------------------------------------------ |
| Character id          | `character_id` (`CHAR_ID_*`, 11 values with forms)                             |
| Character data        | `Character`, `g_Characters[CHARACTER_COUNT]`, `g_CharSlot[id]`                 |
| Party order           | `Party_` owns order: `g_PartyFieldOrder`, `g_PartyBattleOrder`, `g_PartyCount` |
| Battle participants   | `Battler`; `PartyMember`, `EnemyBattler`                                       |
| Enemy definition      | `Enemy` (the BENEMY definition)                                                |
| Script-driven object  | `Actor`, `ACTOR_*`                                                             |
| Field programs        | `PlChar_`                                                                      |
| Battle character bank | `BattlePlayerCharBank`                                                         |

A game object keeps the short noun the disc, the retail text or the reference notes use, without a
system prefix, when the noun means one thing across the game. A system prefix is added only where
two systems have their own thing under one noun. `B` in a disc label marks the battle copy
(`BPLCHAR`, `BENEMY`, `BMAGIC`).

### Disc words

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
shipped containers, not code folders. Where each disc label lives in the tree: [tree](layout.md#tree).

## One name

The same name appears in C, Rust, JSON fields, asset types, docs and the status site. An old name is
deleted, not aliased. A `#define NAME func_<ADDR>` alias is debt to fold into the row, not a name.
Every symbol has one declaration ([lowest scope wins](layout.md#lowest-scope-wins)); a second name for one
address is a cast macro, not a second `extern`. A rename never deletes a fact: the comment moves
with the name.

## Grep

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

## Spelling

US English in prose and in names, as the US game text spells it: `color`, `behavior`, `center`,
`defense`. The project's own words, used in place of the game text's: `Fairy` (`Fairy`, `FAIRY_*`)
for "Faerie". Retail text keeps its spelling (`ITEM_FAERIE_TIARA`, "Faerie Tiara"). SDK names keep
theirs (`CdlPause`, `SpuSetKey`).

## Renames

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

### Rename steps

`tools/symbol.py rename` adds the symbol's `config/symbols.toml` row with its `source`, rewrites every
tracked user (definition, prototypes, uses, `config/`), keeps the address name in a comment and moves
the unit file. Then prove every touched image with `check-<image>`:

```sh
tools/symbol.py rename func_<ADDR> <Name> --image <target> --local --source "<description>" --dry-run
tools/symbol.py rename func_<ADDR> <Name> --image <target> --local --source "<description>"
tools/symbol.py params <Name> old=new ...     # parameter names: definition and prototypes
```

A named symbol is one name in every image: without `--image`, `rename` changes its row in every
table that has it. An address name is unique only per image: `--image <target>` once per image that
holds the twin at that address, `--local` limits the rename to those images' `src/` and `config/`
folders, and `--scope PATH...` names the folders. A twin at another address is another call. The
resident images (`exe/slus_004_22`, `emi/etc/game/00`) rename with no scope. `tools/symbol.py add`
writes a row without a rename, and `tools/symbol.py refs` ranks the units to name first.
