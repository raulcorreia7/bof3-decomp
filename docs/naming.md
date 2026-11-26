# Names

How a function, global, static, constant, macro, type, local, parameter or member is named, in the
game's words. A name needs evidence ([conventions: evidence](conventions.md#evidence)); a thing
with no fact keeps its address name (`func_<ADDR>`, `D_<ADDR>`, `unk_<OFF>`).

## Register

| Thing                                    | Form                        | Example                                  |
| ---------------------------------------- | --------------------------- | ---------------------------------------- |
| system function                          | `TAG_PascalName`            | `SND_SEPlay`, `EMI_Init`                 |
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

## Tags

The tag is the owner: the engine module or the game part that holds the code. System tags are
capitals, as SDL writes them; game tags are words. Every symbol carries one.

**Caller test.** A tag names a layer (`SYS_ GFX_ SND_ EMI_ CD_ INPUT_ Actor_ Script_ Menu_
UI_`) only when several parts call the code. Code one part calls takes that part's tag, wherever its
file sits. A compound tag (`FairyCasino_`) names a part inside a part. The tag is the module the function is linked in and its header, checked against the callers; a subject in the arguments (party, actor, area) never decides it.

Engine modules (`src/engine/<module>`):

| Module                          | Tag                  | Folders                            |
| ------------------------------- | -------------------- | ---------------------------------- |
| boot, threads, frame, bits      | `SYS_`               | `sys/boot`, `sys/flags`            |
| the game's own math             | `MATH_`              | `sys/math`                         |
| pad                             | `INPUT_`             | `input/pad`                        |
| disc drive                      | `CD_`                | `cd/drive`                         |
| LZ77 decoder                    | `LZ77_`              | `cd/lz77`                          |
| EMI archive loader              | `EMI_`               | `emi/loader`                       |
| graphics, fades, palettes       | `GFX_`               | `gfx/*`                            |
| sound, music, SE, XA            | `SND_`               | `sound/*`                          |
| actor records and motion        | `Actor_`             | `actor/task`, `actor/motion`       |
| actor script machine            | `Script_`            | `actor/script`, `actor/ops`        |
| map, cells, heights, encounters | `Area_ AreaAction_`  | `area/*`                           |
| camera                          | `Camera_`            | `camera`                           |
| world-map actors                | `WorldMap_`          | `worldmap`                         |
| party, characters, items        | `Party_ Char_ Item_` | `party/*`                          |
| game loop and modes             | `Game_`              | `state/mode`, `state/progress`     |
| scene host                      | `Scene_`             | `state/scene`                      |
| field to battle hand-over       | `Game_`              | `state/battle`                     |
| text, fonts, glyphs             | `UI_`                | `ui/text`                          |
| windows, frames, boxes, lines   | `UI_`                | `ui/window`                        |
| sprites, icons, cursors         | `UI_`                | `ui/sprite`                        |
| message window and answers      | `UI_`                | `ui/message`, `ui/message_answers` |
| panels and their tasks          | `UI_`                | `ui/panel`, `ui/menu`              |
| list rows and scrollbars        | `UI_`                | `ui/list`                          |
| memory card, save slots         | `SAVE_`              | `overlays/menu/shared`             |
| unnamed files                   | none                 | `slus`, `game/00`                  |

Game parts (`src/overlays`, `src/logo`):

| Part                    | Tag                                                                                                 | Folder                                   |
| ----------------------- | --------------------------------------------------------------------------------------------------- | ---------------------------------------- |
| area load, scene, setup | `Area_ UI_`                                                                                         | `overlays/area`                          |
| battle                  | `Battle_`                                                                                           | `overlays/battle`                        |
| battle magic            | `BMagic_ Effect_`                                                                                   | `overlays/bmagic`                        |
| boss                    | `Boss_`                                                                                             | `overlays/boss`                          |
| player character        | `PlChar_`                                                                                           | `overlays/plchar`                        |
| scenario                | `Scene_ Party_`                                                                                     | `overlays/scenario`                      |
| menu screens            | `Menu_ UI_ Shop_ Master_ Shisu_`                                                                    | `overlays/menu`                          |
| title                   | `Title_`                                                                                            | `overlays/title`                         |
| logo                    | `Logo_`                                                                                             | `logo`                                   |
| fishing pond            | `Fishing_`                                                                                          | `overlays/area`                          |
| fairy village           | `Fairy_ FairyCasino_ FairyNickname_ FairyCopyShop_ FairyMusician_ FairyFortuneTeller_ FairySinger_` | `overlays/commu`, `area175` to `area185` |
| well minigame           | `Well_`                                                                                             | `overlays/area`                          |

A constant or macro takes the tag in capitals (`BATTLE_`, `CAMERA_`). `MATH_TBL`, the EMI archive
magic, is a container tag.

`Field`, `World` and `Etc` are not tags: the disc has `BIN/WORLD##/AREA###` and no other map word. `World_`, `PAD_`, `Mem_`, `Matrix_`, `Data`, `Info` and
`Work` are not tags: use `WorldMap_`, `INPUT_`, `SYS_` and `MATH_`. A disc folder number is a tag only until the area's game term is proven.

A subject with its own family of functions is a tag; a new tag goes into the tables above in the same
change.

The first word after an engine tag is the subsystem (the folder under the module, or a family of three or more functions), and the function says its verb after it: `UI_TextDraw`, `UI_WindowDrawFrame`, `UI_SpriteDraw`, `UI_IconDraw`, `UI_CursorDraw`, `UI_MessageStartArea`, `UI_MessageAnswerSelect`, `UI_PanelOpenTask`, `UI_ListDrawItemRow`, `UI_ModeSet`; `GFX_PaletteLoad`, `GFX_FadeRunBlack`. `Actor_MovementUpdate`, `Script_AnimStepLoop`, `Script_OpsRunFlow`. `EMI_ArchiveLoad`, `EMI_PartyLoadArchives`, `EMI_VabLoadBody`. `Area_SceneInit`, `Area_EncounterPick`, `Area_HeightSample`. A word the subsystem repeats is dropped.

UI parts: shared text, fonts, glyphs and windows are `UI_`; the message window, its panels, answer
lists and area messages are `UI_Message*` and `UI_MessageAnswer*`; panels, cursors, sprites and icons are `UI_Panel*`, `UI_Cursor*`, `UI_Sprite*` and `UI_Icon*`; `Menu_` is only the menu screens' own code, and a widget
copied into another overlay keeps its name; battle panels and numbers are `Battle_`; a screen's own UI
and the numbers, gauges and rows it draws take the screen tag (`Shop_`, `Master_`, `Fairy_`, `SAVE_`,
`Menu_` for the start menu, `Title_` for the title).

## Vocabulary

One word per concept. A new name uses the `Word`; `Rejected` lists the words that name the same
concept. Two words stay only where the definitions differ. A word the SDK, the hardware or one of the
game's own records owns keeps its meaning (`Callback`, `Bank`, `Slot`, `Cell`); the game never renames it.

| Concept                       | Word                                        | Definition                                                                              | Rejected                                                                                                                               |
| ----------------------------- | ------------------------------------------- | --------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| Data table                    | the element plural                          | An indexed sequence in memory, named for the plural of what its index selects           | `Table`, `Array`, `Set`, `Pool`, `Funcs`, `States`, `Handlers`; `List` for a data table; `Steps`/`Modes` only for a step or mode table |
| Sound bank                    | `Bank`                                      | A VAB loaded into one SPU bank slot                                                     | —                                                                                                                                      |
| Buffer                        | `Buffer`                                    | A byte region that data passes through                                                  | `Buf`                                                                                                                                  |
| Queue                         | `Queue`                                     | A first-in first-out list of requests                                                   | —                                                                                                                                      |
| Index                         | `Index`                                     | A position in a runtime array                                                           | `Idx`                                                                                                                                  |
| Id                            | `Id`                                        | The value the retail data stores to identify a thing                                    | —                                                                                                                                      |
| Slot                          | `Slot`                                      | A filled position in a fixed container the player sees                                  | —                                                                                                                                      |
| Count and value               | `Count`, `Value`                            | How many elements a collection holds; a generic number whose role the type names        | `Cnt`, `Num`, `Amount`, `Quantity`                                                                                                     |
| Size                          | `Size`                                      | Bytes of storage a record, buffer or primitive takes                                    | `Len` for bytes                                                                                                                        |
| Length                        | `Length`                                    | The number of elements or characters in a run                                           | `Len`                                                                                                                                  |
| Max and limit                 | `Max`, `Limit`                              | The largest value of a quantity; a bound one operation stays within                     | —                                                                                                                                      |
| Function-pointer element      | `<Role>Callback`                            | A function pointer typed for one signature, named for what the pointed-to function does | `Handler`, `Func`, `Proc`, `Routine`, `Fn`, `Cb`                                                                                       |
| Callback type                 | `Callback`                                  | The no-argument `void (*)(void)` entry                                                  | —                                                                                                                                      |
| Scheduler thread              | `Thread`                                    | One cooperative task the main loop runs each frame                                      | `CallbackSlot`, `Callback` for the slot                                                                                                |
| Event hook                    | `Hook`                                      | A function pointer the engine calls at one event                                        | `Callback` for the pointer                                                                                                             |
| State phase                   | `Mode`, `Step`                              | The phase a mode byte selects; the index a state machine advances                       | `Kind` for either                                                                                                                      |
| Dispatch                      | `Dispatch`                                  | Call one entry of a table by index                                                      | `Handle`                                                                                                                               |
| Initialize                    | `Init`                                      | Bring a system or record to ready for first use                                         | `Setup`, `Create`, `New` as a lifecycle verb                                                                                           |
| Start and begin               | `Start`, `Begin`                            | Begin an ongoing operation; enter a discrete script or record                           | —                                                                                                                                      |
| End                           | `End`                                       | Finish a phase or record                                                                | `Finish`                                                                                                                               |
| Stop, exit, close             | `Stop`, `Exit`, `Close`                     | Stop a playback; leave a system; close a window                                         | —                                                                                                                                      |
| Quit                          | `Quit`                                      | The player's command to abandon an activity (disc word: name entry, shop, fishing)      | `Exit`, `Leave` for it; an SDK shutdown keeps the SDK's `Quit` (`SpuQuit`)                                                             |
| Free, release, remove         | `Free`, `Release`, `Remove`                 | Release a slot; give up a claim; take an element out of a collection                    | `Delete`, `Destroy`, `Kill`                                                                                                            |
| Reset and clear               | `Reset`, `Clear`                            | Restart a system; zero one record's fields                                              | —                                                                                                                                      |
| Open                          | `Open`                                      | Open a player-visible window, panel or shop                                             | —                                                                                                                                      |
| Update, tick, run             | `Update`, `Tick`, `Run`                     | Run a frame; advance a countdown; execute one named action                              | `Exec`, `Process`, `Do`, `Handle` for a frame                                                                                          |
| Read and load                 | `Read`, `Load`                              | Transfer bytes from the device; bring a resource into memory                            | `Fetch`                                                                                                                                |
| Get and find                  | `Get`, `Find`                               | Read one known value; search and return `GAME_NONE`                                     | `Lookup`, `Search` as a verb                                                                                                           |
| Set, write and save           | `Set`, `Write`, `Save`                      | Write one value by key; write a record back; write the memory card                      | `Store`, `Put`                                                                                                                         |
| Yes/no questions              | `Is`, `Has`, `Can`, `Test`                  | A property, a possession, an ability, a flag                                            | `Check`                                                                                                                                |
| Create, alloc, spawn, add     | `Create`, `Alloc`, `Spawn`, `Add`           | Construct an object; claim a slot; place it in the world; append an element             | `Make`, `New` as a creation verb, `Append`, `Insert`                                                                                   |
| Type                          | `Type`                                      | The category a retail value selects                                                     | `Kind`, `Class`                                                                                                                        |
| Flag and flags                | `Flag`, `Flags`                             | One bit; a word of packed bits                                                          | `Bits`                                                                                                                                 |
| Mask                          | `Mask`                                      | A bit pattern that selects bits                                                         | —                                                                                                                                      |
| Timer, counter, frame         | `Timer`, `Counter`, `Frame`                 | A countdown; a count of events; a count of rendered frames                              | `Tick` as a noun for the value                                                                                                         |
| Wait and delay                | `Wait`, `Delay`                             | Hold until a condition; a count of frames before an action                              | —                                                                                                                                      |
| Draw, show, display           | `Draw`, `Show`, `Display`                   | Queue primitives; make a message visible; the hardware display buffer                   | `Render`                                                                                                                               |
| Character and char            | `Character`, `Char`                         | The record and its id; the function and constant tag                                    | `Chara`                                                                                                                                |
| Party, party member, player   | `Party`, `PartyMember`, `Player`            | The group; one member record; a playback object                                         | `Member` for a party member                                                                                                            |
| Enemy and boss                | `Enemy`, `Boss`                             | The BENEMY definition and its battle row; a boss battle module                          | `Monster`                                                                                                                              |
| Message, text and string      | `Message`, `Text`, `String`                 | A message request or window; game text content; a byte sequence                         | `Msg`                                                                                                                                  |
| Anim, animation, motion       | `Anim`, `Animation`, `Motion`               | The actor's animation stream; a frame sequence; physical movement                       | —                                                                                                                                      |
| Effect, magic, ability, skill | `Effect`, `Magic`, `Ability`, `Skill`       | A visual effect; the battle magic program; the ability record; an ability of type SKILL | `Fx`, `Spell`                                                                                                                          |
| Item                          | `Item`                                      | The item records and their ids                                                          | `Goods`                                                                                                                                |
| Area, map, scene, field       | `Area`, `Map`, `Scene`, `Field`             | The level; its grid data; what the scene window runs; the field state                   | —                                                                                                                                      |
| World map                     | `WorldMap`                                  | Code and data only the world-map areas use                                              | `World` in a code name                                                                                                                 |
| Position and geometry         | `Pos`, `Point`, `Coord`, `Vector`, `Offset` | A position value; a point type; a fixed-point coordinate; a math vector; a displacement | —                                                                                                                                      |
| Color, tint, RGB              | `Color`, `Tint`, `RGB`                      | A colour value; a colour delta; the packed pixel format                                 | `Colour`                                                                                                                               |

## Functions

A function name takes one of two orders:

1. **Verb first**, the default: `Tag_VerbObject`. The tag, an underscore, a verb, then the thing
   acted on: `Party_MemberAdd`, `Battle_FindTarget`, `Shop_Buy`.
2. **Object first**, for a family: `Tag_ObjectVerb`. When three or more functions under one tag act
   on the same object, the object comes first, so the family sorts together, as PsyQ writes
   `SsSeqOpen`, `SsSeqPlay` and `SsSeqClose`: `UI_MessageWindowOpen`, `UI_MessageWindowClose`,
   `UI_MessageWindowDraw`.

Count the family across the whole tree. Two functions are not a family. When a third member gets a
name, rename the other two in the same change. A qualifier goes last when two functions differ
(`Battle_TargetNext`, `Battle_TargetPrev`). The subject is the tag, never a word glued to the verb
(`UI_MessageAnswerSelect`). One verb per concept: the [vocabulary](#vocabulary) fixes each verb's meaning. `NextStep` advances a step counter and `SetState` sets a state; `Play`, `Stop`, `Wait` and `Apply` mean what they say.

A function the game calls through a table or a hook takes a plain name for what it does, never a
`Cb`, `Callback` or `Handler` suffix: in PsyQ, `Callback` names the function that registers one. One
function pointer the engine calls at an event is `g_<Tag><Event>Hook`.

**Do**

```c
void Battle_RunAttack(Battler* battler);
u8   Party_FindMember(u8 character_id);   /* GAME_NONE when absent */
void UI_MessageWindowOpen(u8 window_id);    /* one of the UI_MessageWindow family */
s32  UI_MessageWindowIsOpen(u8 window_id);
```

**Don't**

```c
void MessageOpenAnswer(void);   /* no tag */
void UI_MessageOpenWindow(u8 window_id); /* a family member in verb-first order */
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
    /* 0x24 */ Pos2 coord;
} Battler;

void Fairy_SetJob(u8 fairy_index, u8 job_type);
```

**Don't**

```c
typedef struct Battler {
    s16 half_1C;            /* the width and offset, not the role */
    s16 hp2;                /* a guess with a number */
    u8  data[4];
    Pos2 pos_24;
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
shared type, with its comment, so the meaning stays when the layout is reused. A two-letter acronym in a type name is
written in capitals (`UIPanelOrigin`), matching its function tag.

**Do**

```c
/* A point on the 320x240 screen, in pixels. */
typedef Pos2u ScreenPoint;
```

**Don't**

```c
typedef struct { u16 x; u16 y; } ScreenPointData;   /* a second layout, a filler word */
```

A role that recurs gets one typedef over the shared block (`Pos2`, `Pos3`, `Coord3D`, `SVECTOR`,
...), in the header that owns its domain, and every member, parameter and global of that role uses it
(`WorldPos`, `SpriteScale`, `CameraAngle`). A one-off keeps the block type and carries the role in its
member name. Never one typedef per member, never a second layout.

Every module payload starts with `OverlayHeader` (`sys/emi.h`). A prologue that carries more
data is `<Owner>OverlayHeader` and nests it as its first member (`FairyVillageOverlayHeader`); the
word is `Header`, never `Head`.

### Storage words

A name says what a thing is, never how it is stored or found. Drop the storage word; what is left is
usually the name. The same holds for `Ref`, `View`, `Window`, `Row`, `Scratch`, `_ADDRESS` and
`_OFFSET` in a new name.

| The word leaks | Words                                                                        | Write instead                                                                                              |
| -------------- | ---------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| width          | `Byte`, `Half`, `Word`, `Bytes`, `Words`                                     | the role; `unk_<OFF>` until it is known                                                                    |
| shape          | `Record`, `Rec`, `Entry`, `Row`, `Block`, `Chunk`, `Raw`                     | the thing itself: `BattlePanel`, not `BattlePanelRow`                                                      |
| a second view  | `View`, `As<Type>`                                                           | a union member named by role; a byte or half of one value is `LOBU(x)`, `LOH(x)` (`include/common/util.h`) |
| nothing        | `Data`, `Info`, `Obj`, `Object`, `Work`, `Misc`                              | what it holds: `FishingState`, not `Area030Work`                                                           |
| a number       | `Table6`, `Area016`, `Callback3`                                             | what the index selects (`g_BattleCommands`); the place or system once proven (`Fishing`, `Town`)           |
| a category     | `Kind`, `Class`                                                              | `Type`: `BattleOwnerType`, not `BattleOwnerKind`                                                           |
| a saved key    | `Ptr`, `Buf`, `Tmp`, `Cur`, `Num`, `Idx`, `Cnt`, `Obj`, `Ctrl`, `Mgr`, `Spr` | the word: `index`, `count`, `buffer`, `current`, the thing a pointer names                                 |
| a callable     | `Handler`, `Proc`, `Routine`, `Cb`                                           | the action the function runs; `<Role>Callback` for a pointer type, `Callback` for `void (*)(void)`         |

One exception: a record that exists only to make a struct assignment give the retail block move
is a copy unit from `include/common/copy.h` (`Cpy16`, `Cpy16u`), named for its size and
alignment (`u` unaligned) because it has no role.

A storage word stays when it is the game's or the hardware's own term: a save `Slot`, a menu `Row`
the player sees, the PlayStation `Scratchpad`, an SDK name.

## Tables

- A table is the plural of what its index selects, in game terms: `g_Weapons`, `g_AreaEncounters`,
  `g_BattleTurnPhases`, `g_SceneEvents`.
- A sequence is named for what happens.
- A table of the functions a step byte selects is `g_<Owner>Steps`; one a mode byte selects is
  `g_<Owner>Modes`. A step table that must stay a record to match is the record `<Owner>Steps`
  with the member `steps`.
- No wrapper type and none of the [rejected words](#vocabulary) for a data table. A player-visible menu
  list keeps `List`; a map's grid data keeps `Map` (`MapCell`, `AreaMapBundle`).
- The element type carries the mechanism: `<Thing>Func`, one type per signature. The no-argument
  entry `void (*)(void)` is `Callback` (`include/common/callback.h`).
- Until the index is known, a table keeps its address name. Per-image tables of different tasks
  never share a numbered name.

**Do**

```c
typedef void (*BattleCommandCallback)(Battler* battler);

extern Weapon            g_Weapons[WEAPON_COUNT];
extern BattleCommandCallback g_BattleCommands[BATTLE_COMMAND_COUNT];
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

The generic helpers in `include/common/util.h` stay untagged capitals
([helpers](conventions.md#game-helpers)).

## Game terms

| Thing               | Name                                                                                                                                                    |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Character id        | `character_id` (`CHAR_ID_*`, 11 values with forms)                                                                                                      |
| Character data      | `Character`, `g_Characters[CHAR_INDEX_COUNT]`, `g_CharSlot[id]`                                                                                         |
| Battle participants | `Battler`; `PartyMember`, `EnemyBattler`                                                                                                                |
| Enemy definition    | `Enemy` (the BENEMY definition)                                                                                                                         |
| Item category 3     | `Accessory` (`g_Accessories`, `AccessoryId`, `ACCESSORY_*`, `ITEM_CATEGORY_ACCESSORY`): the worn accessories, the fishing lures and the rods, one table |

A game object keeps the short noun the disc, the retail text or the reference notes use, without a
system prefix, when the noun means one thing across the game. A system prefix is added only where
two systems have their own thing under one noun. `B` in a disc label marks the battle copy
(`BPLCHAR`, `BENEMY`, `BMAGIC`).

### Disc words

| Disc label               | Game term                                                                                         |
| ------------------------ | ------------------------------------------------------------------------------------------------- |
| `BATTLE`                 | battle program                                                                                    |
| `BENEMY`                 | `Enemy`                                                                                           |
| `BMAGIC`, `MAGIC#`       | magic (`BMagic_` in battle)                                                                       |
| `PLCHAR`, `BPLCHAR`      | character archive                                                                                 |
| `PLP###`                 | code of one party: the three digits name its characters (`PLP012`: Ryu, Nina, Garr)               |
| `COMMU00` to `COMMU05`   | Fairy Village: the village program (`COMMU00`) and its event scripts (`COMMU01` to `COMMU05`)     |
| `BATE`                   | ability menu (`Game_AbilityMenuLoad` loads it)                                                    |
| `SHISU`                  | the scena11 shisu screen, where the player mixes the four ingredients (`Game_ShisuLoad` loads it) |
| `SISYOU` (師匠)          | `Master` menu                                                                                     |
| `SHOP`                   | shop program                                                                                      |
| `START`                  | start menu                                                                                        |
| `GAME` (slot 0 / slot 1) | engine `game`; `title` screen                                                                     |
| `BGM###`, `COMN_SE`      | music (`BGM`), sound effect (`SE`)                                                                |
| `SCENA##`, `SCE##EF*`    | scene controller, scene effect                                                                    |
| `WORLD##/AREA###`        | area code                                                                                         |
| `SLUS_004.22`            | main executable                                                                                   |
| `LOGO/LOGO.EXE`          | logo player                                                                                       |

Archive families (`BGM`, `BENEMY`, `BOSS`, `BMAGIC`, `BPLCHAR`, `PLCHAR`, `ETC`, `SCENARIO`) name
shipped containers, not code folders. Where each disc label lives in the tree: [tree](layout.md#tree).

## One name

The same name appears in C, Rust, JSON fields, asset types, docs and the status site. An old name is
deleted, not aliased. A `#define NAME func_<ADDR>` alias is debt to fold into the row, not a name.
Every symbol has one declaration ([lowest scope wins](layout.md#lowest-scope-wins)); a second name for one
address is a cast macro, not a second `extern`. A rename never deletes a fact: the comment moves
with the name.

A copy of a function in another image keeps its name. When the same link sees both copies (an overlay
copy of an exe function), the copy takes `<Name>_<ADDR>` at its own address, and its row is an alias
row whose `source` names the copy it duplicates. Never `_<image>`.

## Grep

`git grep -w NAME` finds every use and its evidence, so each fact has one spelling and sits on one
line.

- Write a name in full. Build no name by token pasting (`##`) and split none across lines when the
  match allows it.
- A table row is one line: a `config/symbols/<image>.toml` row, a data-table entry, a `@source` line.
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

Acronyms follow the SDK library their value belongs to, and are capitals otherwise. The drive is
`Cd` (libcd: `SYS_ReadCd`, `g_CdStateHandlers`), the sound library is `Snd` in a type (`SndBank`,
libsnd's `SndVolume`), and `XA`, `HP`, `AP`, `BGM` and `SE` are capitals (`SND_XAIsIdle`,
`SND_XAStateIdle`). `SE` is the disc's word for a sound effect, as `BGM` is for music
(`BIN/BATTLE/BATL_SE`, `COMN_SE`): `SND_SEPlay(u16 se_id)`.

## Renames

A rename is one change: the evidence row, every user in C, Rust, JSON, the docs and the wiki, and
the unit file named for the function, proven byte-exact in every touched image. Search for the
address and the old name as well as the new one ([steps](#rename-steps)).

A named function or global keeps its address name in a one-line comment directly above its
definition and its header declaration, so a search for the address name from assembly, a diff or
old notes still finds it. The rename that names the address writes the line.

```c
/* func_801F2C04 */
MATCH void UI_MessageAnswerOpen(void) {
    WORLD_ARM_ANSWER_MESSAGE_IDLE(2, 4);
}

/* D_80148627 */
extern volatile u8 g_BattlePanelStep;
```

### Rename steps

`tools/symbol.py rename` adds the symbol's `config/symbols/<image>.toml` row with its `source`, rewrites every
tracked user (definition, prototypes, uses, `config/`), keeps the address name in a comment and moves
the unit file. Then prove every touched image with `check-<image>`:

```sh
tools/symbol.py rename func_<ADDR> <Name> --image <target> --local --source "<description>" --dry-run
tools/symbol.py rename func_<ADDR> <Name> --image <target> --local --source "<description>"
tools/symbol.py params <Name> old=new ...     # parameter names: definition and prototypes
```

A named symbol is one name in every image, so `rename` changes its row in every table that has it. An
address name is unique only per image: give `--image <target>` once per image that holds the twin at
that address; a twin at another address is another call. `--local` or `--scope PATH...` limits the
files; the resident images (`exe/slus_004_22`, `emi/etc/game/00`) rename with no scope.
`tools/symbol.py add` writes a row without a rename, and `tools/symbol.py refs` ranks the units to
name first.
