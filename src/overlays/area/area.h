#ifndef OVERLAY_AREA_AREA_H
#define OVERLAY_AREA_AREA_H

/* The area group's declarations: the symbols two or more area images read or call. */

#include "game.h"
#include "area/map.h"
#include "sys/exe.h"
#include "sys/scene.h"
#include "gfx/vram.h"
#include "area/fishing.h"
#include "sys/actor.h"
#include "menu/inventory.h"
#include "menu/panel.h"
#include "scenario/party.h"
#include "common/facing.h"
#include "scenario/runtime.h"
#include "common/util.h"
#include "area/effects.h"

/* One cell of a payload's data tables: `offset` is the table's byte offset and
 * `index` the byte offset of the row. */
#define AREA_PAYLOAD_FIELD(payload, type, offset, index) (*(type*)&(payload)[(offset) + (index)])

/* The first payload word of a world area overlay, at its load address: the module id the
 * loader checks against the archive TOC (@source: wiki:formats/emi#code-overlays). */
#define AREA_MODULE_ID(area)                             (52 + (area))

/* One cell of a payload's quad table: the map cell the quad sits on, as x and y, and the signed
 * depth of its base. Every area's floor payload carries such a table. */
typedef struct AreaQuadCell {
    u8 x;
    u8 y;
    s8 z;
} AreaQuadCell;

ASSERT_SIZE(AreaQuadCell, 3);

/* One quad of an area part table: the packed cell word (bytes: depth row, shape, cell y,
 * cell x) and the tile word Area_ApplyTileToQuad reads. */
typedef struct AreaQuadPart {
    union {
        u32 packed;
        u8  bytes[4];
    } cell;

    u32 tile;
} AreaQuadPart;

ASSERT_SIZE(AreaQuadPart, 8);

/* A span of map cells: the first column and row, then the column and row it stops before. */
typedef struct AreaCellSpan {
    u8 x0;
    u8 y0;
    u8 x_end;
    u8 y_end;
} AreaCellSpan;

ASSERT_SIZE(AreaCellSpan, 4);

/* The per-sprite transform state at 0x800E4940 (0x18-byte stride): the halfword translation base,
 * the normal and the rotation angles. */
typedef struct AreaTransform {
    /* 0x00 */ u16 base_x;
    /* 0x02 */ u16 base_y;
    /* 0x04 */ u16 base_z;
    /* 0x06 */ u16 pad_06;
    /* 0x08 */ union {
        SVECTOR vec;
        u16     word[4];
    } normal;

    /* 0x10 */ SVECTOR rotation;
} AreaTransform;

ASSERT_OFFSET(AreaTransform, base_x, 0x00);
ASSERT_OFFSET(AreaTransform, normal, 0x08);
ASSERT_OFFSET(AreaTransform, rotation, 0x10);
ASSERT_SIZE(AreaTransform, 0x18);

/* One panel marker row selected by a controller mask: the mask, the panel
 * step it selects and an unused byte. */
typedef struct WorldMapMarker {
    u16           mask;
    /* 0x02 */ u8 step;
    u8            pad_03;
} WorldMapMarker;

ASSERT_SIZE(WorldMapMarker, 4);

/* One fishing location row: the location type a WorldMapPoint carries, then the five fish ids
 * the location lists on the Fishing_ShowLocation message. */
typedef struct FishingLocationRow {
    u8 type;       /* 0x00 */
    u8 fish_id[5]; /* 0x01 */
} FishingLocationRow;

ASSERT_SIZE(FishingLocationRow, 6);

/* One world key row: the key matched against g_GameEntryAreaId and the mode it
 * selects. The area key tables are scanned at a 4-byte stride by
 * WORLD_MAP_SELECT_KEY_SCRIPT. */
typedef struct WorldMapKey {
    u16 key;    /* 0x00 */
    u8  mode;   /* 0x02 */
    u8  unk_03; /* 0x03 */
} WorldMapKey;

ASSERT_SIZE(WorldMapKey, 4);

/* One 2-byte cell of the torch gauge's bar texture: the clut byte and the texture column of the
 * cell. Area104 indexes the arrow cells of its two states and area121 the bar's two states. */
typedef struct TorchGaugeCell {
    u8 clut; /* 0x00 */
    u8 u;    /* 0x01 */
} TorchGaugeCell;

/* The torch gauge cells, one per gauge state. */
typedef struct TorchGaugeCells {
    TorchGaugeCell rows[2]; /* 0x00 */
} TorchGaugeCells;

ASSERT_SIZE(TorchGaugeCell, 0x02);
ASSERT_OFFSET(TorchGaugeCell, u, 0x01);
ASSERT_SIZE(TorchGaugeCells, 0x04);
ASSERT_OFFSET(TorchGaugeCells, rows, 0x00);

/* D_80143F06 */
extern u8       g_GameLastCellType;
extern s16      D_801448EE;
void            Area_SpawnWeightedActor(void);
void            func_801F2C18(void);
void            func_801F2C30(void);
/* func_801F2C38 */
void            func_801F2C48(void);
void            func_801F2C5C(void);
s32             Area_TestStepTrigger(s32 x, s32 y);
void            func_801F2C88(void);
void            func_801F2C8C(void);
void            func_801F2D18(void);
void            func_801F2D3C(void);
/* D_801D4285 */
extern u8       g_MenuMasterStep;
void            func_801F2E1C(void);
void            func_801F2ED8(void);
void            func_801F2EEC(void);
void            func_801F2F24(void);
void            func_801F309C(void);
void            func_801F3120(void);
void            func_801F314C(void);
void            func_801F31EC(void);
void            func_801F3244(void);
void            func_801F3264(void);
/* func_801F3400 */
void            Actor_SetScreenOrigin(void);
/* func_801F3360 */
void            Actor_ZoomOut(void);
/* func_801F33A8 */
extern u8       D_801F2DD4[];
void            Area_StartDirectionalScript(Actor* actor);
void            func_801F34E0(void);
void            func_801F35FC(void);
void            func_801F3690(void);
void            func_801F36A4(void);
void            func_801F3750(void);
void            func_801F385C(void);
void            func_801F38DC(void);
void            func_801F39BC(void);
void            func_801F39D8(s32 x, s32 y, u32 sprite_id);
void            Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id);
void            func_801F3A64(void);
void            func_801F3A78(void);
void            func_801F3D28(void);
void            Area_DrawGradientDiamond(s16 x, s16 y);
void            Area_DrawHudBanner(s16 x, s16 y);
void            func_801F4178(void);
void            func_801F41D8(void);
void            func_801F455C(void);
void            Area_AddCameraOffsetY20(void);
void            Area_SubCameraOffsetY20(void);
void            func_801F45CC(void);
void            func_801F4768(void);
extern u8       D_801F3424[];
extern u8       D_801F4624[];
extern Callback D_801F4F64[];
extern u8       D_801F5364[];

extern Callback D_801F5804[];

/* Ask Actor_ClaimSlot what the party battler in `slot` finds at its position: aim the task at the battler, look the party slot's selection up in `table`, run the probe of `type`, and store a found result in the battler's unk_0B. */
static inline void Area_ProbeParty(s32 slot, const u8* table, s32 type) {
    PartyMember* battler;
    u8           index;
    s16          y;
    s16          x;
    u8           selection;
    s32          result;

    SELF_SET(&g_Game.members[slot]);
    index     = g_PartyFieldOrder[slot];
    y         = g_Game.members[slot].screen_y.signed_value;
    x         = g_Game.members[slot].screen_x.signed_value;
    selection = table[index];
    result    = Actor_ClaimSlot(type, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        battler               = SELF(PartyMember);
        battler->param.unk_0B = (u8)result;
    }
}

/* Walk the map bundle's object list g_AreaMapBundle.object_list_28 through func_801576FC until its zero
 * terminator. */
static inline void Area_RunBundleObjects(void) {
    u8* record;

    record = MEM_PTR(u8, MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4);
    while (FIELD(u32, record, 0) != 0) {
        func_801576FC(record);
        record += FIELD(u16, record, 2) * 4 + 4;
    }
}

/* A cell and facing that starts a scene event at the given step. */
typedef struct SceneTrigger {
    u8 x;
    u8 y;
    u8 facing;
    u8 step;
} SceneTrigger;

ASSERT_SIZE(SceneTrigger, 0x4);

/* The body of a scene trigger check `u8 f(u8 x, u8 y)`: the party at (x, y) facing the leader's way stands on one of
 * the `count` triggers of `table`. It starts the scene event `mode` at the trigger's step and returns 1, else returns
 * 0. A block statement macro: it declares a local, so it is the first statement of the function. */
#define AREA_START_SCENE_TRIGGER(table, count, scene_mode)                                                     \
    s32 i;                                                                                                     \
                                                                                                               \
    for (i = 0; i < (count); i++) {                                                                            \
        if (x == (table)[i].x && y == (table)[i].y && ((table)[i].facing & 0xF) == g_Game.members[0].facing) { \
            break;                                                                                             \
        }                                                                                                      \
    }                                                                                                          \
    if (i == (count)) {                                                                                        \
        return 0;                                                                                              \
    }                                                                                                          \
    Game_SetScriptActive();                                                                                    \
    g_SceneEventState.mode = (scene_mode);                                                                     \
    g_SceneEventState.step = (table)[i].step;                                                                  \
    return 1

/* Whether a step to (x, y) enters the trigger band that starts at `first_row`: with the scene ready it clears
 * the first script variable and runs script entry 0, which starts the area scene and blocks the step. */
static inline s32 Area_StepIntoTrigger(s32 x, s32 y, s32 first_row) {
    if (g_GameCellType == 2 && SYS_TestFlag(g_SceneEventFlags, 0x33) != 0 && (u32)((x >> 16) - 70) < 3U) {
        if ((u32)((y >> 16) - first_row) < 3U && (g_Game.members[0].facing == FACING_UP_LEFT || (u32)(g_Game.members[0].facing - 6) < 2U)) {
            *g_ScriptVars = 0;
            Scene_SetupParty(0);
            return 1;
        }
    }
    return 0;
}

/* Store the step the cell code under the party leader's next position selects, then run it from `steps`.
 * A plain-block statement macro: as an inline the function is longer, and `do { } while (0)` adds an
 * instruction. */
#define AREA_STEP_BY_CELL_CODE(steps)                                                                          \
    {                                                                                                          \
        s32    x;                                                                                              \
        s32    y;                                                                                              \
        s32    scaled;                                                                                         \
        Actor* scratch;                                                                                        \
                                                                                                               \
        scaled = g_Game.members[0].unk_0C * g_Game.members[0].unk_09;                                          \
        x      = FIX_INT(g_Game.members[0].pos.x.fixed + scaled);                                              \
        y      = FIX_INT(g_Game.members[0].pos.y.fixed + g_Game.members[0].unk_10 * g_Game.members[0].unk_09); \
                                                                                                               \
        scratch     = g_Self;                                                                                  \
        scratch->vx = x;                                                                                       \
        scratch->vy = y;                                                                                       \
                                                                                                               \
        /* The step stores re-read the work cell: the compiler must assume a call may have changed it. */      \
        if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xA1) {                                                    \
            SELF(Actor)->param.unk_0B = 1;                                                                     \
        } else if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xA0) {                                             \
            SELF(Actor)->param.unk_0B = 2;                                                                     \
        } else if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xAE) {                                             \
            SELF(Actor)->param.unk_0B = 3;                                                                     \
        } else if (g_Game.walk_flags & AREA_WALK_TRANSITION) {                                                 \
            SELF(Actor)->param.unk_0B = 4;                                                                     \
        } else {                                                                                               \
            SELF(Actor)->param.unk_0B = 0;                                                                     \
        }                                                                                                      \
                                                                                                               \
        steps[SELF(Actor)->header.mode]();                                                                     \
    }

/* Write the actor index of `record` (its distance from the actor table `base`) in script variable 3 as its own block; `part` and `step` are the caller's pinned temporaries. */
#define AREA_WRITE_SCRIPT_RECORD_INDEX(record, base, part, step) \
    do {                                                         \
        (record) = (Actor*)((s32)(record) - (base));             \
        (part)   = ((s32)(record) << 3) - (s32)(record);         \
        (part)   = ((part) << 2) - (s32)(record);                \
        (step)   = ((part) << 9) - (part);                       \
        (part)   = (step) << 18;                                 \
        (step)   = -((step) + (part));                           \
        (step) >>= 3;                                            \
        g_ScriptVars[3] = (s8)(step);                            \
    } while (0)

void Area_DrawHud(s16 x, s16 y);

void Actor_StopMoving(void);
void Area_ClearWorkColumn(void);
u8*  Area_FindFreeWorkRow(void);
void Area_InitSpin(SpinEffect* spin);
void Area_UpdateRunGauge(void);
void Area_ClaimSpawnSlot(void);
s32  Area_UpdateSpawnSlots(void);
void Area_DrawSpawnSlot(AreaSpawnSlot* slot);
void Area_EndTurn(void);
u8   Area_StartTurn(s32 direction, s32 previous);

/* func_801F4A34 (area104/14), func_801F4F78 (area121/14) */
s32 Actor_FacingToward(s32 x, s32 y, u8 row);

#endif
