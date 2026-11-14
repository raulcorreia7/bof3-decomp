#ifndef AREA_AREA_H
#define AREA_AREA_H

/* A world area: the map bundle the area program loads at 0x80104000 (grid
 * dimensions, per-cell corner heights, tile rectangles, the per-cell byte-code
 * table, and the object and record lists), the scene/step table at 0x800E3800
 * and the area script table at 0x800D3800. The area overlays build the field
 * mesh, place objects and run the area script from these bytes; the game
 * overlay queries the same grid. Format: @source: wiki:formats/area.
 *
 * Readers: `exe/slus_004_22@0x80155560` indexes the interleaved tile table offsets;
 * `exe/slus_004_22@0x8014DD3C` stores scene record byte +0x07 at work+0x2C and
 * `exe/slus_004_22@0x8014D6DC` uses it as a script-table index.
 *
 * Per-cell byte-code values, record-list opcodes and `scroll_1E` have no known
 * meaning and keep offset names.
 *
 * One definition per world object: the area overlays include this header
 * instead of redeclaring a record (@source: wiki:formats/area).
 *
 * The formats:
 *
 * - `AreaMapBundle` and its cell rows: map bundle.
 * - `AreaActorDef`, `AreaActorDefs`: scene/step table.
 * - `AreaScripts`, `AreaScriptSection`: area script table.
 * - `AreaTrail`, `AreaSlotWork`, `UPoint2D`: neighboring buffers; the
 *   area program owns them.
 *
 * The format sections are in @source: wiki:formats/area.
 */

#include "types.h"
#include "common/fixed.h"
#include "common/vector.h"
#include "psx/psyq.h"

/* The world overlays' own records. Every area program keeps its scratch in
 * the `0x800E4800` window (@source: wiki:formats/area#neighboring-buffers):
 * the AREA027 trail rows, the AREA028 slot rows and the AREA028 position ring
 * live there, each overlay reading its own shape of the same bytes. */

#define AREA_MAP_BUNDLE_SIZE             0x30

/* The opcode mask of each record list's first byte: the +0x20 list keeps six
 * bits, the +0x22 list seven (Area_RunBundleOpcodes/Area_RunBundleRecords). */
#define WORLD_BUNDLE_OPCODE_MASK         0x3F
#define WORLD_BUNDLE_RECORD_OPCODE_MASK  0x7F

/* A scenario script owns the field while the active bit is set. */
#define GAME_SCRIPT_ACTIVE()             (g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE)

#define AREA_MAP_CELL_RECORD_SIZE        0x04

#define AREA_TILE_RECT_SIZE              0x04

#define AREA_TILE_QUAD_SIZE              0x08

#define AREA_MAP_LIST_RECORD_HEADER_SIZE 0x04

#define AREA_MAP_CELL_HEADER_SIZE        0x04

#define AREA_MAP_OBJECT_HEADER_SIZE      0x04

#define AREA_ACTOR_DEF_SIZE              0x08

#define AREA_WORK_POINTERS_SIZE          0x10

/* The palette arena: one 16 KB CLUT arena (256 units of 0x40 bytes) that the
 * area, ETC, BATTLE and BMAGIC families fill in slices, with a working copy the
 * engine uploads wholesale when `g_GfxPalettePending` is set (`@0x8014E22C`, 32 rows of
 * 0x200 bytes; `@0x8014E284` does the copy). `include/gfx/prim.h:23` names
 * the working copy. */
#define AREA_PALETTE_ARENA               0x80033800u /* offset 0 in the arena */
#define AREA_PALETTE_ARENA_33A00         0x80033A00u /* +0x200, 512 B; panel colors at +8 */
#define AREA_PALETTE_ARENA_33C00         0x80033C00u /* +0x400, 512 B, BMAGIC/BATTLE */
#define AREA_PALETTE_ARENA_33E00         0x80033E00u /* +0x600, 1024-6144 B, 200 archives */
#define AREA_PALETTE_ARENA_35800                         \
    0x80035800u /* +0x2000, 1024-3584 B, no literal    \
                                        * reader: reached through the base */
/* The working copy of the palette banks (g_GraphicsPaletteDst): palette animations and fades write it, and the pending
 * flag g_GfxPalettePending asks the next frame to upload it. */
#define AREA_PALETTE_WORK          0x80037800u
/* The script tables g_Scripts alternates between: the field's, the battle's and the battle magic's. */
#define AREA_SCRIPT_TABLE          0x800D3800u
#define BATTLE_SCRIPT_TABLE        0x800F0800u
#define BMAGIC_SCRIPT_TABLE        0x800C3800u
#define AREA_PALETTE_UNIT          0x40u  /* one CLUT entry */
#define AREA_PALETTE_ROW           0x200u /* one upload row (32 rows) */

/* The area view space: a cell is 0x80 units wide and cell 128 sits on the origin;
 * a cell's centre is half a cell past its corner. */
#define AREA_CELL_ORIGIN           0x4000
#define AREA_CELL_HALF             0x40
#define AREA_CELL_GRID_ROWS        56          /* rows of the cell grids: g_AreaCellGrid and g_AreaCells */
#define AREA_CELL_GRID_COLS        28          /* columns of the cell grids */
#define MAP_BUNDLE_BASE            0x80104000u /* the map bundle */

/* The payload-head id convention: an area program is 52 + area, an auxiliary
 * module is 0xFC-0x104. The loader's identity check is implicit otherwise. */
#define AREA_PROGRAM_ID_BASE       52u
#define AREA_AUX_ID_FIRST          0xFCu
#define AREA_AUX_ID_LAST           0x104u

/* The area program's work memory (AreaWorkPointers.work_08). */
#define AREA_WORK                  0x800E4800u

#define WORLD_VERTEX_POINT_SIZE    0x06

#define WORLD_VERTEX_RECORD_SIZE   0x28

/* The trail row: 0x98 bytes. The AREA027 program keeps three of them at
 * `0x800E4800` (`@0x801F2D5C` walks them with that stride) and stages each
 * one through `@0x801F2E3C` and `@0x801F304C`. */
#define WORLD_TRAIL_SIZE           0x98
#define WORLD_TRAIL_MAX            32
#define WORLD_TRAIL_COUNT          3

#define WORLD_SLOT_WORK_SIZE       0x10
#define WORLD_WORK_SLOT_COUNT      32u
#define WORLD_WORK_SLOT_STRIDE     0x10u

#define WORLD_RING_ENTRY_COUNT     32

/* One area slot's message record: WORLD_ShowAreaSlotMessage shows messages[i]
 * through func_80150224 for the first tag that equals byte 0 of a battle
 * record row. Each area program holds its records back to back (1-7 per
 * image, for example world04/area197/13 at 0x801F4A2C). */
#define PARTY_MEMBER_MESSAGE_COUNT 4
#define PARTY_MEMBER_MESSAGE_SIZE  0x0C

/* `0x80104000` - the map bundle: a fixed 0x30-byte header of `u16` section
 * offsets in 4-byte units, then the per-cell tables. Readers: the area init
 * `@0x80153DE8` (publishes the byte-code base into `g_AreaCellCodes`), the height
 * query `@0x8015477C` (119 overlay call sites), the mesh builders and the
 * record-list interpreters `@0x801576FC`, `@0x80157F98`, `@0x801580A4`,
 * `@0x80158B24`, `@0x8015507C`, `@0x80155B40`; the grid readers live in
 * emi/etc/game/00 (`@0x8019C4F0`, `@0x8019C794`, `@0x8019EC20`). */
typedef struct AreaMapBundle {
    u8  width;                       /* 0x00 - grid width in cells */
    u8  height;                      /* 0x01 */
    u16 grid_off4_02;                /* 0x02 - cell grid, 4-byte units:
                                *        (0x30 + width*height*4 + align4(width*height)) / 4 */
    u16 tile_table_offsets_04[4][2]; /* 0x04-0x13 - [selector][table], A then B */
    u16 byte_code_off4_14;           /* 0x14 - per-cell byte-code table (`g_AreaCellCodes`):
                                *        (0x30 + width*height*4) / 4; equals
                                *        width*height + 12 in 200/200 payloads */
    u16 zero_16;                     /* 0x16 - zero in 200/200, no reader */
    u16 zero_18;                     /* 0x18 - zero in 200/200, no reader */
    u16 color_1A[2];                 /* 0x1A-0x1D - runtime color words, written by the engine
                                *            (`@0x801583BC` is the only header store) and
                                *            read at `0x8010401A + (mask >> 3) * 2` */
    u16 scroll_1E;                   /* 0x1E - shipped 0xF300-0xFA90 in 76/200, meaning open */
    u16 list_base_20;                /* 0x20 - record list, opcode byte & 0x3f */
    u16 list_base_22;                /* 0x22 - record list, opcode byte & 0x7f */
    u16 record_region_24;            /* 0x24 - indexed by the 4-byte-unit ids in g_AreaCellGrid */
    u16 zero_26;                     /* 0x26 - zero in 200/200, no reader */
    u16 object_list_28;              /* 0x28 - tag + body size, walked by the map interpreter */
    u16 height_off4_2A;              /* 0x2A - height-byte table; u16[+0x2A]*4 == size in 187
                                *        payloads, == size - width*height in the rest */
    u16 zero_2C;                     /* 0x2C - zero in 200/200, no reader */
    u16 zero_2E;                     /* 0x2E - zero in 200/200, no reader */
} AreaMapBundle;

ASSERT_SIZE(AreaMapBundle, AREA_MAP_BUNDLE_SIZE);
ASSERT_OFFSET(AreaMapBundle, width, 0x00);
ASSERT_OFFSET(AreaMapBundle, height, 0x01);
ASSERT_OFFSET(AreaMapBundle, grid_off4_02, 0x02);
ASSERT_OFFSET(AreaMapBundle, tile_table_offsets_04, 0x04);
ASSERT_OFFSET(AreaMapBundle, byte_code_off4_14, 0x14);
ASSERT_OFFSET(AreaMapBundle, list_base_20, 0x20);
ASSERT_OFFSET(AreaMapBundle, height_off4_2A, 0x2A);

extern AreaMapBundle g_AreaMapBundle;

/* Word bits of D_80146258, the world input/scheduler lock word. Bit 3 skips
 * Area_AdvanceScroll; bit 6 blocks the menu request; bit 8 is set while a
 * scenario script owns the field. */
typedef enum GameFlags {
    GAME_FLAG_SCROLL_LOCK   = 1 << 3,
    GAME_FLAG_MENU_LOCK     = 1 << 6,
    GAME_FLAG_SCRIPT_ACTIVE = 1 << 8,
} GameFlags;

/* The world entry/step busy word. Bit n of the low three marks party slot n still busy with an entry. */
typedef enum AreaWalkFlags {
    AREA_WALK_BUSY_ALL             = (1 << 0) | (1 << 1) | (1 << 2),
    AREA_WALK_ENTRY_ACTIVE         = 1 << 3,
    AREA_WALK_ACCEPT_LOCK          = 1 << 4,
    AREA_WALK_ENTRY_PENDING        = 1 << 6,
    AREA_WALK_LEADER_SWITCH_ACTIVE = 1 << 10,
    AREA_WALK_MENU_ACTIVE          = 1 << 11,
    AREA_WALK_TRANSITION           = 1 << 12,
    AREA_WALK_MAP_LOADING          = 1 << 15,
} AreaWalkFlags;

/* Modes of the field task (g_Task->header.mode) that the pad requests start. */
typedef enum FieldTaskMode {
    FIELD_TASK_MODE_LEADER_SWITCH   = 3,
    FIELD_TASK_MODE_MENU            = 4,
    FIELD_TASK_MODE_CLIMB           = 8,
    FIELD_TASK_MODE_PERSONAL_ACTION = 0x0A,
} FieldTaskMode;

/* g_Game.current->u.field.mode_12B while the character field action runs. */
#define GAME_PANEL_MODE_PERSONAL_ACTION 8

/* Garr pushes after walking this many frames against an object. */
#define GARR_PUSH_HOLD_FRAMES           0x10

/* g_Game.current->u.field.counter_11C, the walk speed index: Teepo and Peco act on a rock only at the run index. */
#define FIELD_SPEED_RUN                 4

/* One +0x24 cell record: four signed corner heights, loaded as s8 by
 * `@0x801530D0`, `@0x8015684C` and `@0x80157CE4`.
 */
typedef struct AreaCellCorners {
    s8 corner_height_00[4];
} AreaCellCorners;

ASSERT_SIZE(AreaCellCorners, AREA_MAP_CELL_RECORD_SIZE);

/* The g_AreaCellPrims row bits of AreaCell.prim_id. */
#define AREA_CELL_PRIM_MASK 0xFFF

/* One cell of the 56 x 28 screen grid: the tile it shows (the grid-wrapped panel position that
 * Area_GetCell stores) and its row in g_AreaCellPrims (0 = none). */
typedef struct AreaCell {
    u8  tile_x;
    u8  tile_y;
    u16 prim_id; /* low 12 bits: the g_AreaCellPrims row; upper bits are flags */
} AreaCell;

extern AreaCell g_AreaCells[AREA_CELL_GRID_ROWS][AREA_CELL_GRID_COLS];
/* Zero in the load image: 0x400 rows of one POLY_FT4 per display buffer
 * (g_FrameBufferIndex). In a row's second record, pad1 and pad2 hold the rows of the two linked
 * cells (0 = none); in its first, pad1 holds the pending upload request. */
extern POLY_FT4 g_AreaCellPrims[][2];
extern u16      g_AreaCellPrimFreeIds[0x400];
extern u16      g_AreaCellPrimFreeIndex;
extern s16      g_AreaGridColCursor;
extern s16      g_AreaGridRowCursor;

/* Four-byte tile table A rectangle. */
typedef struct AreaTileRect {
    u8 dv_00;
    u8 du_01;
    u8 v_02;
    s8 u_03; /* signed: `lb a0,3(a1)` at 0x80155670; 0x80 reads as -128 */
} AreaTileRect;

ASSERT_SIZE(AreaTileRect, AREA_TILE_RECT_SIZE);

/* Eight-byte tile table B descriptor: four UV pairs. */
typedef struct AreaTileQuad {
    u8 uv_pairs_00[4][2];
} AreaTileQuad;

ASSERT_SIZE(AreaTileQuad, AREA_TILE_QUAD_SIZE);

/* +0x20/+0x22 list entry header; the body follows as u32 words. */
typedef struct AreaMapListHeader {
    u8 operand_00[2];
    u8 word_count_02; /* includes this 4-byte header */
    u8 opcode_03;
} AreaMapListHeader;

ASSERT_SIZE(AreaMapListHeader, AREA_MAP_LIST_RECORD_HEADER_SIZE);

/* +0x24 cell header; words_02 includes this header and its record chain. */
typedef struct AreaMapCellHeader {
    u8  y_00;
    u8  x_01;
    u16 words_02;
} AreaMapCellHeader;

ASSERT_SIZE(AreaMapCellHeader, AREA_MAP_CELL_HEADER_SIZE);

/* +0x28 object header; the body follows as body_words_02 words. */
typedef struct AreaMapObjectHeader {
    u16 tag_00;
    u16 body_words_02;
} AreaMapObjectHeader;

ASSERT_SIZE(AreaMapObjectHeader, AREA_MAP_OBJECT_HEADER_SIZE);

/* `0x800D3800` - the area script table, a table of actor animation streams: a
 * `u32` directory, then per section a `u16` slot table followed by its
 * records. Each record is one stream (see `Actor_StageAnimStep`). `dir_bytes == 4 * L` is the
 * directory's own size, not an entry count: read as a count it overruns the
 * payload (`WORLD00/AREA016.EMI` slot 4: `u32[0] = 28`, `u32[29] = 0x240018` in
 * 2,708 bytes). The only reader is `exe/slus_004_22@0x8014D6DC`, which reaches
 * the block through `g_Scripts`: `section = u32[table + 4*lhu(work+0x2C)]`,
 * `record = table + section + u16[table + section + 2*lbu(work+0x4B)]`, stored to
 * `work+0x50`. The battle overlays swap `BATTLE_SCRIPT_TABLE` in for the duration of a
 * battle handler. */
typedef struct AreaScripts {
    u32 dir_bytes;      /* 0x00 - == 4 * L, the directory's own size */
    u32 section_off[1]; /* 0x04 - L-1 entries, block-relative, strictly increasing */
} AreaScripts;

/* One section: `slots_bytes == 2 * M`, and the distinct `record_off` values
 * increase strictly and tile the section, one stream each. The last section
 * runs to the end of the block. */
typedef struct AreaScriptSection {
    u16 slots_bytes;   /* 0x00 - == 2 * M */
    u16 record_off[1]; /* 0x02 - M entries, relative to the section base */
} AreaScriptSection;

/* `0x800E3800` - the scene table: a `u32` count then 8-byte records.
 * `exe/slus_004_22@0x8014DD3C` copies `script_section` to work+0x2C;
 * `@0x8014D6DC` uses it as a script-table directory index and
 * `@0x80167E00` compares it before resolving the record id in a terminated
 * list. `D_801459F4` publishes the record array at `0x800E3800 + 4`. */
typedef enum SpriteTextureMode {
    SPRITE_TEXTURE_MODE_0  = 0,
    SPRITE_TEXTURE_MODE_1  = 1,
    SPRITE_TEXTURE_MODE_2  = 2,
    SPRITE_TEXTURE_MODE_3  = 3,
    SPRITE_TEXTURE_MODE_4  = 4,
    SPRITE_TEXTURE_MODE_9  = 9,
    SPRITE_TEXTURE_MODE_10 = 10,
} SpriteTextureMode;

typedef struct AreaActorDef {
    u16 id;             /* 0x00 - match key in @0x8014DD3C and @0x80167E00 */
    u16 clut_select;    /* 0x02 - low byte to work+0x27; the u16 is work+0x2C */
    u8  texture_page;   /* 0x04 - to work+0x25 (4 distinct values) */
    u8  texture_v;      /* 0x05 - to work+0x26 (31 distinct values) */
    u8  texture_mode;   /* 0x06 - to work+0x28; the 9 and 10 cases belong to actor +0x06 */
    u8  script_section; /* 0x07 - copied to work+0x2C; script-table index */
} AreaActorDef;

ASSERT_SIZE(AreaActorDef, AREA_ACTOR_DEF_SIZE);

typedef struct AreaActorDefs {
    u32          count_00;   /* 0x00 - == (size - 4) / 8 in 200/200, count 4-51 */
    AreaActorDef records[1]; /* 0x04 */
} AreaActorDefs;

/* `0x801459F0` - the four pointers the loader publishes together. Each word has
 * its own name in the tree (`g_Scripts` the script table, `D_801459F4` the scene
 * records); this type is what a reader casts the address to when it wants all
 * four, so the words keep their own declarations. */
typedef struct AreaWorkPointers {
    u32 script_table_00;  /* 0x00 -> 0x800D3800 (swapped per battle handler) */
    u32 scene_records_04; /* 0x04 -> 0x800E3804 */
    u32 work_08;          /* 0x08 -> 0x800E4800 */
    u32 code_base_0C;     /* 0x0C -> 0x800F5000 */
} AreaWorkPointers;

ASSERT_SIZE(AreaWorkPointers, AREA_WORK_POINTERS_SIZE);

/* One AREA024 vertex row: four packed points at +0x02. The program copies
 * 0x28-byte rows (`emi/world00/area024/14@0x801F3314`) and advances both
 * buffers by 0x28 (`@0x801F362C`). */
typedef struct AreaVertex {
    u16     unk_00;
    Point3D points[4]; /* 0x02 */
    u8      unk_1A[0x0E];
} AreaVertex;

ASSERT_SIZE(AreaVertex, WORLD_VERTEX_RECORD_SIZE);
ASSERT_OFFSET(AreaVertex, points, 0x02);

typedef struct AreaTrail {
    Point3DL pos;                     /* 0x00 - the head anchor */
    s32      unk_0C;                  /* 0x0C */
    s32      radius;                  /* 0x10 - the ring radius */
    u16      angle;                   /* 0x14 - the rotation angle */
    u16      pad_16;                  /* 0x16 */
    DVECTOR  points[WORLD_TRAIL_MAX]; /* 0x18 - the trail points */
} AreaTrail;

ASSERT_SIZE(AreaTrail, WORLD_TRAIL_SIZE);
ASSERT_OFFSET(AreaTrail, points, 0x18);

#define AREA_SPAWN_SLOT_COUNT 8

/* One entry of the spawn table: a shrinking glow disc at an actor position. */
typedef struct AreaSpawnSlot {
    u8       active;        /* 0x00 - 0 marks a free slot */
    u8       unk_01;        /* 0x01 */
    u8       life_02;       /* 0x02 - frames left; counts down and frees the slot at 0 */
    u8       unk_03;        /* 0x03 */
    WorldPos pos;           /* 0x04 */
    u8       unk_10[4];     /* 0x10 */
    u16      radius_14;     /* 0x14 - disc radius, shrinks every frame */
    u8       core_shade_16; /* 0x16 - shade at the disc centre */
    u8       rim_shade_17;  /* 0x17 - shade at the disc rim */
} AreaSpawnSlot;

ASSERT_SIZE(AreaSpawnSlot, 0x18);
ASSERT_OFFSET(AreaSpawnSlot, pos, 0x04);
ASSERT_OFFSET(AreaSpawnSlot, radius_14, 0x14);
ASSERT_OFFSET(AreaSpawnSlot, core_shade_16, 0x16);
ASSERT_OFFSET(AreaSpawnSlot, rim_shade_17, 0x17);

#define AREA_RING_POINTS     16
#define AREA_RING_ANGLE_STEP 0x100

/* A ring of glow points around `center`: screen positions of the ring points, projected each frame. */
typedef struct AreaRing {
    s32     base[3];                  /* 0x00 */
    s32     unk_0C;                   /* 0x0C */
    s32     center[3];                /* 0x10 - the ring centre */
    s32     unk_1C;                   /* 0x1C */
    s16     radius;                   /* 0x20 */
    u8      unk_22;                   /* 0x22 */
    u8      unk_23;                   /* 0x23 */
    DVECTOR screen_base;              /* 0x24 */
    DVECTOR screen_center;            /* 0x28 */
    DVECTOR screen[AREA_RING_POINTS]; /* 0x2C - one screen position per ring point */
} AreaRing;

ASSERT_OFFSET(AreaRing, radius, 0x20);
ASSERT_OFFSET(AreaRing, screen, 0x2C);

/* The AREA028 slot row: 0x10 bytes. The program keeps 32 of them at
 * `0x800E4800` (`@0x801F2F5C`, `@0x801F3004`, `@0x801F3060` walk them with
 * that stride) and the ring projection reads the active one. */
typedef struct AreaSlotWork {
    u8                unk_00[4];
    Point2D           offset;
    s16               scale; /* 0x08 - the projection scale */
    s16               unk_0A;
    volatile UPoint2D screen;
} AreaSlotWork;

ASSERT_SIZE(AreaSlotWork, WORLD_SLOT_WORK_SIZE);
ASSERT_OFFSET(AreaSlotWork, screen, 0x0C);

typedef struct PartyMemberMessages {
    u8  tags[PARTY_MEMBER_MESSAGE_COUNT];     /* 0x00 */
    s16 messages[PARTY_MEMBER_MESSAGE_COUNT]; /* 0x04 message ids */
} PartyMemberMessages;

ASSERT_SIZE(PartyMemberMessages, PARTY_MEMBER_MESSAGE_SIZE);
ASSERT_OFFSET(PartyMemberMessages, tags, 0x00);
ASSERT_OFFSET(PartyMemberMessages, messages, 0x04);

/* Finds the scene-table record for a wanted scene id and fills its palette and
 * tile fields (exe/slus_004_22@0x8014DD3C). */

/* The area functions the resident tables and the area images call. */
void Message_RunAreaMessage();
void Actor_ClearVelocity();
void func_801CF564();
void func_801CFB40();
void func_801CFF20();
void func_801F2C14();
void Fishing_ShowLocation();
void func_801F2C3C();
void func_801F32C0();
void func_801F341C();
void func_801F34A0();
void func_801F36D4();
void func_801F38C0();
void func_801F3A8C();
void func_801F3F80();
void func_801F40AC();
void func_801F418C();
void func_801F41B0();
void func_801F41D0();
void func_801F4494();
void func_801F4C84();
void func_801F4D80();
void func_801F512C();
void func_801F52F8();

/* The area functions the resident tables and the area images call. */
void func_801F3224();
void Actor_NextStep(void);
void func_801F3608();
void func_801F37B4();
void func_801F3DCC();
void Actor_Fly(void);
void func_801F45E4();
void Area_DrawScreenTint();
void Actor_FreePaletteFades();
void Actor_Reveal();
void Actor_TrackFocus();
void GFX_DrawShadedDisc(s16, s16, s16, u8, u8);
void Scene_ClearActor();

#endif
