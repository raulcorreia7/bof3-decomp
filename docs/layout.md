# Layout

Where source, headers and symbols live, and how a header is laid out.

## Header layout

A name appears before its first use. A header holds, in order: the guard and includes; the
constants and enums several records share; one block per record in table order (its sizes, its ID
`enum` in value order, its struct, its asserts, its `extern`); prototypes in address order. Asserts
follow their struct: `ASSERT_OFFSET` in offset order, then `ASSERT_SIZE`.

Every header that carries a guard names it from its target: `include/common/util.h` is
`COMMON_UTIL_H`, a group header `src/overlays/plchar/Char_Foo.h` is `PLCHAR_CHAR_FOO_H`, and an image
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
| EMI archives, the disc file list, the LZ77 stream, SEP and BGM banks, the BGM selection table, cue tables, overlay headers, script tables             | ours, one per format     |
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
| Audio                   | `include/audio/*.h`                                                                                 | audio cues, VAB data, audio state                                              |
| Disc and file formats   | `include/sys/{cd_format,emi,lz77,str}.h`, `include/audio/{bank,bgm,cue,sep,vab}.h`                  | one self-contained header per format ([format headers](#format-headers))       |
| Text                    | `include/game/{encoding,text}.h`                                                                    | text encodings, control codes, text records                                    |
| Game records            | `include/game/*.h`                                                                                  | shared database records: items, abilities, characters, enemies, genes, fairies |
| Menu                    | `include/menu/*.h`, `include/sys/gameui.h`                                                          | menu panels, inventory, party selection, saves, shops                          |
| Area                    | `include/area/*.h`                                                                                  | area tasks, maps, area data                                                    |
| Battle                  | `include/battle/*.h`                                                                                | battle handlers, actors, work records, battle state                            |
| Scene                   | `include/scenario/*.h`                                                                              | scene steps and effects shared across images                                   |
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
| L3    | `sys`, `gfx`, `area`               |
| L4    | `common.h`, `etc`, `menu`          |
| L5    | `game`, `scenario`                 |
| L6    | `battle`                           |
| L7    | `slus`                             |
| L8    | `game.h`                           |

`game.h` stays small: the base and the headers every group needs. A group header
(`src/overlays/<group>/<group>.h`, `src/shared/etc.h`, `src/engine/slus/slus.h`) includes `game.h`
and the subsystem headers its images use; an image header includes its group header; a `.c` includes
its image header and nothing else. A subsystem header leaves `game.h` once no group outside the ones
that include it needs it.

### Globals

A global is one `extern` with its real type in the owning header, a name and an address. The address
is a `config/symbols.toml` row, or the name itself for an address name (`D_80145E90`). C and headers keep the address name in a comment as described in [renames](naming.md#renames).
Retail RAM address literals stay out of C and headers; hardware registers, the scratchpad range,
BIOS addresses and format offsets stay as defines.

A named global lives in the header of the system that owns it, beside the code that reads and
writes it: `g_SndBGMId` in the sound runtime header, `g_Battle.state` in `battle/records.h`. Each system
header stays self-contained. An executable word with no name yet is declared at the lowest scope that
covers its users ([lowest scope wins](#lowest-scope-wins)); one that several families read is in
`include/slus/data.h` or `include/slus/functions.h`, in address order. The change that names one moves
its `extern` to the owner.

Adjacent globals that form one record are [one struct or array](conventions.md#globals-are-records).

One name per address per image. A second name for one address (a width or `volatile` view) is a cast
macro, not a second `extern`. A cast macro that names the object itself keeps the bytes
(`#define g_Task ((T *)g_Task)`); an address-taking view hoists the address and changes them.

- `g_Task` is the pointer cell at `0x1F800044`: one `extern struct Task *g_Task;` in
  `include/psx/mem.h`. `struct Task` is incomplete, so no member is reachable without a view. Each
  mode header views the cell as its work record through a cast macro. Code with no record type reads
  bytes through `TASK_BYTES[n]`, and assigns the cell with `(struct Task *)`. An image that reads
  it as `volatile` defines `TASK_VOLATILE` before the first include.
- Task header: every record the cell points at starts with the same three bytes: `flags` (0x00),
  `mode` (0x01) and `step` (0x02). A type with a `u8` there uses these names, not `unk_01` or
  `state_02`. Per-object scratch (fishing, a boss) is a union at the record's tail, one view per
  user (`ext.fishing`), at the same offsets.

#### Order-sensitive macros

Four macros select one declaration, so the `#define` comes before the image's first include. The
header reads the macro when it is first included; a later `#define` changes nothing. Each pair of
declarations has one name and gives a different qualifier or width, so a pair is not a duplicate to
merge, and the macro is not a setting to move into a header.

| Macro                               | Header                  | Selects                                             |
| ----------------------------------- | ----------------------- | --------------------------------------------------- |
| `TASK_VOLATILE`                     | `include/psx/mem.h`     | `volatile` view of `g_Task`                         |
| `SCRIPT_VARS_VOLATILE`              | `include/game/script.h` | `volatile u8 g_ScriptVars`                          |
| `GRAPHICS_PALETTE_PENDING_VOLATILE` | `include/slus/data.h`   | `volatile u8 g_GfxPalettePending`                   |
| `GAME_SCRATCH_BASE_SCALAR`          | `include/game/spawn.h`  | `u8 D_1F800000[]` in place of the `ScratchPad` view |

## Unit files

splat names an unnamed unit by its uppercase hex offset. When its functions are known, one
`git mv` renames it, in one commit with every row that names the file (`splat.yaml`). The source folder of a target is what
`source_folder` in `tools/bof3/resolve/ids.py` returns.

## Symbols and the link

A global's address is its row in `config/symbols.toml`, or the name itself for an address name
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
