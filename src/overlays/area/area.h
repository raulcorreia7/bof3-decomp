#ifndef OVERLAY_AREA_AREA_H
#define OVERLAY_AREA_AREA_H

/* The area group's declarations: the symbols two or more area images read or call. */

#include "game.h"
#include "sys/exe.h"
#include "sys/scene.h"
#include "gfx/vram.h"
#include "area/fishing.h"
#include "sys/actor.h"
#include "menu/inventory.h"
#include "menu/panel.h"
#include "menu/party.h"
#include "slus/facing.h"
#include "scenario/runtime.h"
#include "common/util.h"

/* The first payload word of a world area overlay, at its load address: the module id the
 * loader checks against the archive TOC (@source: wiki:formats/emi#code-overlays). */
#define AREA_MODULE_ID(area) (52 + (area))

/* One panel marker row selected by a controller mask: the mask, the panel
 * step it selects and an unused byte. */
typedef struct WorldMapMarker {
    u16           mask;
    /* 0x02 */ u8 step;
    u8            unk_03;
} WorldMapMarker;

ASSERT_SIZE(WorldMapMarker, 4);

/* One 4-byte map point: the x and y bytes, then the class byte and a pad byte. */
typedef struct WorldMapPoint {
    u8 x;      /* 0x00 */
    u8 y;      /* 0x01 */
    u8 unk_02; /* 0x02 */
    u8 unk_03; /* 0x03 */
} WorldMapPoint;

ASSERT_SIZE(WorldMapPoint, 4);

/* One world key row: the key matched against g_GameContextSeed and the mode it
 * selects. The area key tables are scanned at a 4-byte stride by func_801F30EC
 * and its per-area twins. */
typedef struct WorldMapKey {
    u16 key;    /* 0x00 */
    u8  mode;   /* 0x02 */
    u8  unk_03; /* 0x03 */
} WorldMapKey;

ASSERT_SIZE(WorldMapKey, 4);

extern u8       D_80143F06;
extern s16      D_801448EE;
extern u8       D_80146867;
extern u8       D_80147ACF;
void            Area_SpawnWeightedActor(void);
void            func_801F2C14(void);
void            func_801F2C18(void);
void            func_801F2C30(void);
/* func_801F2C38 */
void            Fishing_ShowLocation(void);
void            func_801F2C48(void);
void            func_801F2C5C(void);
s32             Area_CheckStepTrigger(s32 x, s32 y);
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
void            Actor_CenterOnScreen(void);
/* func_801F3360 */
void            Actor_ZoomOut(void);
void            func_801F33A8(void);
void            func_801F341C(void);
extern u8       D_801F2DD4[];
void            Area_StartDirectionalScript(Actor* actor);
void            func_801F34A0(void);
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
void            func_801F4534(void);
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

/* Ask func_8015CB18 what the party battler in `slot` finds at its position: aim the task at the battler, look the party slot's selection up in `table`, run the probe of `kind`, and store a found result in the battler's unk_0B. */
static inline void Area_ProbeParty(s32 slot, const u8* table, s32 kind) {
    PartyMember* battler;
    u8           index;
    s16          y;
    s16          x;
    u8           selection;
    s32          result;

    TASK_SET(&g_Game.members[slot]);
    index     = g_PartyFieldOrder[slot];
    y         = g_Game.members[slot].unk_30.signed_half;
    x         = g_Game.members[slot].unk_2E.signed_half;
    selection = table[index];
    result    = func_8015CB18(kind, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        battler               = (PartyMember*)g_Task;
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

/* The body of a scene trigger check `u8 f(u8 x, u8 y)`: the party at (x, y) facing the leader's way stands on one of
 * the `count` triggers of `table`. It starts the scene event `mode` at the trigger's step and returns 1, else returns
 * 0. A block statement macro: it declares a local, so it is the first statement of the function. */
#define AREA_START_SCENE_TRIGGER(table, count, mode)                                                           \
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
    g_SceneEventMode = (mode);                                                                                 \
    g_SceneEventStep = (table)[i].step;                                                                        \
    return 1

/* Whether a step to (x, y) enters the trigger band that starts at `first_row`: with the scene ready it clears
 * the first script variable and runs script entry 0, which starts the area scene and blocks the step. */
static inline s32 Area_StepIntoTrigger(s32 x, s32 y, s32 first_row) {
    if (D_80143F03 == 2 && SYS_TestFlag(g_SceneEventFlags, 0x33) != 0 && (u32)((x >> 16) - 70) < 3U) {
        if ((u32)((y >> 16) - first_row) < 3U && (g_Game.members[0].facing == FACING_UP_LEFT || (u32)(g_Game.members[0].facing - 6) < 2U)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
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
        scratch     = g_Task;                                                                                  \
        scratch->vx = x;                                                                                       \
        scratch->vy = y;                                                                                       \
                                                                                                               \
        /* The step stores re-read the work cell: the compiler must assume a call may have changed it. */      \
        if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {                                                    \
            g_Task->param.unk_0B = 1;                                                                          \
        } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {                                             \
            g_Task->param.unk_0B = 2;                                                                          \
        } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {                                             \
            g_Task->param.unk_0B = 3;                                                                          \
        } else if (g_Game.walk_flags & AREA_WALK_TRANSITION) {                                                 \
            g_Task->param.unk_0B = 4;                                                                          \
        } else {                                                                                               \
            g_Task->param.unk_0B = 0;                                                                          \
        }                                                                                                      \
                                                                                                               \
        steps[g_Task->header.mode]();                                                                          \
    }

void Area_DrawHud(s16 x, s16 y);

void Actor_StopMoving(void);
void Area_ClearWorkColumn(void);
u8*  Area_FindFreeWorkRow(void);
void Area_InitSpin(void* spin);
void Area_UpdateRunGauge(void);
void Area_ClaimSpawnSlot(void);
s32  Area_UpdateSpawnSlots(void);
void Area_DrawSpawnSlot(AreaSpawnSlot* slot);
void Area_EndTurn(void);
u8   Area_StartTurn(s32 direction, s32 previous);

#endif
