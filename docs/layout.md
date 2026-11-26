# Layout

Where source, headers and symbols live, and how a header is laid out.

## Header layout

A name appears before its first use. A header holds, in order: the guard and includes; the
constants and enums several records share; one block per record in table order (its sizes, its ID
`enum` in value order, its struct, its asserts, its `extern`); prototypes in address order. Asserts
follow their struct: `ASSERT_OFFSET` in offset order, then `ASSERT_SIZE`.

Every header that carries a guard names it from its target: `include/common/util.h` is
`COMMON_UTIL_H`, a group-wide header `src/overlays/plchar/shared/Char_Foo.h` is `PLCHAR_CHAR_FOO_H`, and an image
header is `OVERLAY_<GROUP>_<ARCHIVE>_<SLOT>_H` from its target id, so `emi/world02/area104/14` is
`OVERLAY_WORLD02_AREA104_14_H`. A shared body header has no guard.

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

## Files and headers

Where source, headers and symbols live. One source tree publishes the matched C and a
byte-identical image, so a path answers which binary and which function a source belongs to.

### Tree

| Path                                      | Holds                                                                                           |
| ----------------------------------------- | ----------------------------------------------------------------------------------------------- |
| `src/engine/<system>/`                    | code every overlay calls, one folder per system, from the executable (`slus`) and `game/00`     |
| `src/engine/slus/`, `src/engine/game/00/` | what has no system yet: unnamed `func_` files, data files and the image header                  |
| `src/logo/`                               | the logo player, a separate executable with its own address space                               |
| `src/overlays/<group>/<archive>/<slot>/`  | one overlay image: its disc archive and slot, in the group that loads it                        |
| `src/overlays/<group>/<group>.h`          | the group header                                                                                |
| `src/overlays/<group>/shared/<Name>.h`    | a body or header shared by images of one group; `area/worlds/world0N.h` holds the world headers |
| `src/shared/<Name>.h`                     | a body or header shared by images of several groups                                             |

A shared body sits at the lowest folder that holds every image that includes it: the image folder, then
`overlays/<group>/shared/Name.h`, then `shared/Name.h`.

Groups: `area`, `battle`, `bmagic`, `boss`, `commu`, `menu`, `plchar`, `scenario`, `title`.
Disc words in folders: `COMMU00` to `COMMU05` are `overlays/commu/commu00` to `commu05`; `BATE` and
`SHISU` are `overlays/menu/bate/00` and `overlays/menu/shisu/00`; `PLP012` is `overlays/plchar/plp012/00`.
The glosses are in [naming: disc words](naming.md#disc-words).
Id to path: `emi/<family>/<archive>/<slot>` lives in `src/<root>/<archive>/<slot>`, where `<root>` is
`overlays/<family>` unless the `source_folder` table in `tools/bof3/resolve/ids.py` names another;
`exe/slus_004_22` is `src/engine/slus` and `exe/logo` is `src/logo`.
An engine image takes its files from several folders: a `c` row names a file outside the image folder
by its path from that folder (`[0xC6D00, c, ../sound/SND_Init]`; `../../sound/SND_Init` in `game/00`).
A system folder holds the files of both engine images, and the row says which image links a file.
A named file lives in the module folder of its name prefix: `sys` (boot, flags, math), `input/pad`, `cd`
(drive, `lz77`), `emi/loader`, `gfx` (palette, fade, prim), `sound` (seq, vab, xa, se), `sdk` (PsyQ
members), `actor` (ops, script, motion, task), `area` (map, collision, encounter, action), `camera`, `worldmap`, `ui` (text, message, message_answers, menu), `party` and `state` (mode, progress, scene,
battle). The module boundaries are designed, not proven by the bytes, except `ui/message_answers` and
`actor/ops`. A file keeps its image folder until it is named.
`config/` and `build/asm/` follow the id, which is the disc path; `src/` follows what the code does.

The path tells the build which image a source belongs to, except in an engine system folder, where the
image's `c` row does; the build needs no source list.

### Numbered leaves

The last segment, `<slot>`, is the image's entry index in its EMI archive. The number names no role:
the role follows the entry's load address, which each `config/emi/**/splat.yaml` holds in `vram`.

### Files

- One function per file is the default: a function gets its own file once it is split out, and the
  file is named for it. A `.c` file is one `c` row of its image's `splat.yaml`; it holds several
  functions only where that row covers them ([multi-function units](#multi-function-units)).
- A `.c` file is a matching unit, not a claimed original source file. Files merge into one claimed
  original unit only with evidence (rodata order, an SDK member object, a jump table), cited once
  where the merge is made.
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

### Multi-function units

A `.c` file holds several functions only where one `c` row of its image's `splat.yaml` covers them
(`BMagic_Effect.c`, offset-named files, hand-named files).
[Matching](matching.md#a-function-in-a-file-with-other-functions) describes the split.

### Translation units of an image

An image's text run is one translation unit: `<archive>_<slot>.c` in the image folder (for example
`src/overlays/area/area157/13/area157_13.c`) holds the image header include and one
`#include "Name.c"` per function file, in link order. A shared body is included by its own path
(`#include "shared/Area_RoundSpriteCoordinate.h"`), so the image keeps no thin wrapper: an edit to
the body reaches the executable and every overlay that includes it. The function files stay as they
are, so matching and review work per function, and the image's `splat.yaml` holds one `c` row for
the run (`[0x4, c, area157_13]`). `tools/check_sources.py` counts a source that a row's unit includes
as named.

To convert an image:

1. Check that the `c` rows of one segment are contiguous and every function is matched (no
   `NON_MATCHING`, no `INCLUDE_ASM`, no file-scope `static`).
2. Write `<archive>_<slot>.c` from the rows in order, include each shared body in place of its thin
   wrapper and delete the wrapper, then replace those rows by the one row at the first offset. A
   per-unit switch (`FAKE_DECL_TASK_VOLATILE`) applies to the whole unit, so every function of the
   run must take it or none.
3. Run `meson setup --reconfigure build/meson`, then `ninja -C build/meson check-<image>` and the
   full `pre-push`.

A run that holds a proven object edge is several units, one `c` row each (`plchar_turn_script`,
`plchar_ryu_walk`, ...): the edge is a function run that recurs in the same order in three or more
images, so each such run, and each stretch between two runs, is one unit named for its role and
what it holds. A stretch without such evidence stays one unit. Each unit's `.rodata` and `.data`
owner rows take the unit's name.

The boundary is the text run: a `.data`, `.rodata` or `.bss` run, a draft or `INCLUDE_ASM` function,
or the module-id word ends it. A function source that also feeds another row's section (a shared
body with its own `.rodata`, as in `area175/13`) is not a clean run: the link fails with a section
discarded from the shared object. Leave that image per function until the sources split.

### Engine modules

A designed engine module is one translation unit and one header, as a PsyQ library is one object and one
header. `<module>.c` includes the module's function files in link order, with the unnamed functions
between them (`src/engine/gfx/fade/fade.c`); one `c` row at the first offset names it, and the unit
may include files of other module folders by their path from `src/`. `<module>.h` holds the public
prototypes, the types the module owns and its globals as `extern`; the image header and the `include/slus`
headers include it. A prototype that only the executable and `game/00` sources saw stays out of the overlays'
view in a second block of the header, behind `ENGINE_LOCAL_DECLS`: an overlay that calls the function without
a prototype compiles the call differently. A module whose functions are not contiguous in link order stays one unit per function
file, or joins its neighbour where the bytes need it (`emi/loader/emi.c` holds the CD drive states of
`cd/drive`, which interleave with the loader). A function with `INCLUDE_ASM` stays out of a unit: the
split assembly is named for the row; `actor/ops`, `area/action` and `gfx/palette` of `game/00` also stay per function, because
their jump-table `.rodata` alternates with `.data` rows of other objects, which one unit cannot hold. `game/00` is never one unit: `"%d"` is pooled twice in its
`.rodata`, so `Actor_DrawValueDigits` and `AreaAction_FindSmall` lie in different objects.

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
| EMI archives, the disc file list, the LZ77 stream, SEP and BGM banks, the BGM selection table, SE tables, overlay headers, script tables              | ours, one per format     |
| STR and XA sector geometry and the XA subheader (`str.h`)                                                                                             | ours: PsyQ leaves it out |
| VAB (`VabHdr`, `ProgAtr`, `VagAtr`), TIM (`TIM_IMAGE`), CD positions and files (`CdlLOC`, `CdlFILTER`, `CdlFILE`), the STR sector header (`StHEADER`) | PsyQ's own type          |

**Do**

```c
/* emi.h: an EMI archive, as stored on the disc. */
#include "types.h"

#define EMI_SECTOR_SIZE 2048

typedef struct EMIEntry {
    /* 0x00 */ u32 size;
    /* 0x04 */ u32 offset;
} EMIEntry;
ASSERT_SIZE(EMIEntry, 0x8);
```

**Don't**

```c
/* emi.h */
#include "types.h"
#include "audio/bank.h"           /* another system */

typedef struct EMIEntry { u32 size; u32 offset; } EMIEntry;

extern u8 g_EmiLoaderState;       /* runtime state in a format header */
void      EMI_Init(void);   /* code in a format header */
```

### Domains

| Domain                  | Headers                                                                                             | Owns                                                                           |
| ----------------------- | --------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| System: kernel          | `include/sys/{intr,math,sched,scene}.h`                                                             | interrupt callbacks, scheduling, system math routines                          |
| System: tasks           | `include/sys/{actor,task}.h`                                                                        | task state shared across images                                                |
| System: memory          | `include/sys/scratchpad.h`, `include/psx/mem.h`                                                     | RAM-backed system records, scratchpad views, memory-map access                 |
| System: CD and files    | `include/sys/cd.h`                                                                                  | CD command, file and stream state                                              |
| Graphics                | `include/gfx/*.h`                                                                                   | drawing primitives, VRAM records, graphics state                               |
| Audio                   | `include/audio/*.h`                                                                                 | audio SEs, VAB data, audio state                                               |
| Disc and file formats   | `include/sys/{cd_format,emi,lz77,str}.h`, `include/audio/{bank,bgm,se,sep,vab}.h`                   | one self-contained header per format ([format headers](#format-headers))       |
| Text                    | `include/game/{encoding,text}.h`                                                                    | text encodings, control codes, text records                                    |
| Game records            | `include/game/*.h`                                                                                  | shared database records: items, abilities, characters, enemies, genes, fairies |
| Menu                    | `include/menu/*.h`                                                                                  | menu panels, inventory, saves, shops                                           |
| Area                    | `include/area/*.h`                                                                                  | area tasks, maps, area data                                                    |
| Battle                  | `include/battle/*.h`                                                                                | battle handlers, actors, work records, battle state                            |
| Scene                   | `include/scenario/*.h`                                                                              | scene steps, effects and the party formation shared across images              |
| Overlay loading         | `include/sys/{emi,exe,loader_tail}.h`, `include/etc/overlay.h`                                      | EMI and executable loading, overlay tables                                     |
| Main executable exports | `include/slus/*.h`                                                                                  | `SLUS_004.22` symbols the overlays read or call                                |
| Platform and matching   | `include/types.h`, `include/common/*.h`, `include/psx/*.h`, `include/psyq/*.h`, `include/match/*.h` | C widths, shared helpers, PSX and PsyQ interfaces, match-only helpers          |

### Include layers

A header in `include/` includes only its own folder and lower layers, so the include graph has no
cycle at file or folder level. A name a higher layer owns is reached through that layer's header
or moves down to the lowest layer that covers its users ([lowest scope wins](#lowest-scope-wins)).

| Layer | Folders and headers                |
| ----- | ---------------------------------- |
| L0    | `psyq`                             |
| L1    | `types.h`                          |
| L2    | `common/`, `audio`, `psx`, `match` |
| L3    | `gfx`, `sys`                       |
| L4    | `common.h`, `area`, `etc`          |
| L5    | `game`                             |
| L6    | `battle`                           |
| L7    | `scenario`                         |
| L8    | `menu`                             |
| L9    | `slus`                             |
| L10   | `game.h`                           |

`game.h` stays small: the base and the headers every group needs. A group header
(`src/overlays/<group>/<group>.h`, `src/shared/etc.h`, `src/engine/slus/slus.h`) includes `game.h`
and the subsystem headers its images use; an image header includes its group header; a `.c` includes
its image header and nothing else. A subsystem header leaves `game.h` once no group outside the ones
that include it needs it.

### Globals

A global is one `extern` with its real type in the owning header, a name and an address. The address
is a `config/symbols/<image>.toml` row, or the name itself for an address name (`D_80145E90`). C and headers keep the address name in a comment as described in [renames](naming.md#renames).
Retail RAM address literals stay out of C and headers; hardware registers, the scratchpad range,
BIOS addresses and format offsets stay as defines.

A named global lives in the header of the system that owns it, beside the code that reads and
writes it: `g_SndBGMId` in the sound runtime header, `g_Battle.state` in `battle/records.h`. Each system
header stays self-contained. An executable word with no name yet is declared at the lowest scope that
covers its users ([lowest scope wins](#lowest-scope-wins)); one that several families read is in
`include/slus/data.h` or `include/slus/<domain>.h` (`area`, `sound`, `system`, `actor`, `ui`, `party`; `functions.h` includes them and keeps the rest), in address order. The change that names one moves
its `extern` to the owner.

Adjacent globals that form one record are [one struct or array](conventions.md#globals-are-records).

One name per address per image. A second name for one address (a width or `volatile` view) is a cast
macro, not a second `extern`. A cast macro that names the object itself keeps the bytes
(`TASK(Type)` is `((Type*)g_Task)`); an address-taking view hoists the address and changes them.

- `g_Task` is the scratchpad cell at `0x1F800044`: the record whose handler is running. A dispatcher
  sets it before each handler (`Actor_DispatchAll`, `Party_RunFrame`, `Battle_UpdateEffects`); code that
  runs another record's handler saves it first and restores it after. The record's type follows the
  mode (`Actor` on the field, `PartyMember` for a battler, the effect's own record in a spell effect,
  `FishingState` while fishing), so `struct Task` in `include/psx/mem.h` is incomplete and no member is
  reachable without a view. Read `TASK(Type)->member`; set `TASK_SET(record)`; save and restore through a
  typed local or `TASK(void)`; read the bytes of an untyped record through `TASK_BYTES[n]`. An image
  that reads it as `volatile` defines `FAKE_DECL_TASK_VOLATILE` before the first include.
- Task header: every record the cell points at starts with the same three bytes: `flags` (0x00),
  `mode` (0x01) and `step` (0x02). A type with a `u8` there uses these names, not `unk_01` or
  `state_02`. Per-object scratch (fishing, a boss) is a union at the record's tail, one view per
  user (`ext.fishing`), at the same offsets.

#### Order-sensitive macros

Four macros select one declaration, so the `#define` comes before the image's first include. The
header reads the macro when it is first included; a later `#define` changes nothing. Each pair of
declarations has one name and gives a different qualifier or width, so a pair is not a duplicate to
merge, and the macro is not a setting to move into a header.

| Macro                                         | Header                  | Selects                                               |
| --------------------------------------------- | ----------------------- | ----------------------------------------------------- |
| `FAKE_DECL_TASK_VOLATILE`                     | `include/psx/mem.h`     | `volatile` view of `g_Task`                           |
| `SCRIPT_VARS_VOLATILE`                        | `include/game/script.h` | `volatile u8 g_ScriptVars`                            |
| `FAKE_DECL_GRAPHICS_PALETTE_PENDING_VOLATILE` | `include/slus/data.h`   | `volatile u8 g_GfxPalettePending`                     |
| `FAKE_DECL_GAME_SCRATCH_BASE_SCALAR`          | `include/game/spawn.h`  | `u8 g_ScratchPad[]` in place of the `ScratchPad` view |
| `ENGINE_LOCAL_DECLS`                          | engine module headers   | the prototypes only the executable and `game/00` see  |

## Unit files

splat names an unnamed unit by its uppercase hex offset. When its functions are known, one
`git mv` renames it, in one commit with every row that names the file (`splat.yaml`). The source folder of a target is what
`source_folder` in `tools/bof3/resolve/ids.py` returns.

## Symbols and the link

A global's address is its row in `config/symbols/<image>.toml`, or the name itself for an address name
(`D_80145E90`). `g_Task` is one row in the `["exe/slus_004_22"]` table. The row is the whole
edit: the link finds the address by itself, with no per-image list to extend and no reconfigure.

```toml
["exe/slus_004_22"]
g_Task = { addr = 0x1F800044, size = 0x4, source = "..." }
```

Rows are written in address order. Keys: `addr`; `type` and `size` for splat; `source` (what the symbol is or does);
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
