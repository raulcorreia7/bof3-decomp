#ifndef OVERLAY_AREA_AREA_H
#define OVERLAY_AREA_AREA_H

/* The area group's declarations: the symbols two or more area images read or
 * call. A world header includes this file; an image header includes its world
 * header. */

#include "game.h"
#include "sys/exe.h"
#include "sys/scene.h"
#include "gfx/vram.h"
#include "area/fishing.h"
#include "work/actor.h"
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
void            Fish_LocationMessage(void);
void            func_801F2C48(void);
void            func_801F2C5C(void);
s32             Area_CheckStepTrigger(s32 x, s32 y);
void            func_801F2C88(void);
void            func_801F2C8C(void);
void            func_801F2D18(void);
void            func_801F2D3C(void);
/* D_801D4285 */
extern u8       g_MasterStep;
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
void            Actor_ShrinkAndFinish(void);
void            func_801F33A8(void);
void            func_801F341C(void);
extern u8       D_801F2DD4[];
void            Area_StartDirectionalScript(Actor* actor);
void            func_801F34A0(void);
void            func_801F34E0(void);
void            func_801F358C(void);
void            func_801F35E0(void);
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
s16             func_801F4158(DVECTOR* a, DVECTOR* b, DVECTOR* c);
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

/* Ask func_8015CB18 what the party battler in `slot` finds at its position: aim the task at the battler,
 * look the party slot's selection up in `table`, run the probe of `kind`, and store a found result in the
 * battler's unk_0B. Every change here must verify every member. */
static inline void Area_ProbeParty(s32 slot, const u8* table, s32 kind) {
    PartyBattler* battler;
    u8            index;
    s16           y;
    s16           x;
    u8            selection;
    s32           result;

    TASK_SET(&g_BattlePartyBattlers[slot]);
    index     = g_PartyFieldOrder[slot];
    y         = g_BattlePartyBattlers[slot].unk_30.signed_half;
    x         = g_BattlePartyBattlers[slot].unk_2E.signed_half;
    selection = table[index];
    result    = func_8015CB18(kind, 0, selection, x, y);
    if ((u8)result != GAME_NONE) {
        battler               = (PartyBattler*)g_Task;
        battler->param.unk_0B = (u8)result;
    }
}

void Area_DrawHud(s16 x, s16 y);

void Actor_StopMoving(void);
void Area_ClearWorkColumn(void);
u8*  Area_FindFreeWorkRow(void);
void Area_InitSpin(void* spin);
void Area_StepRunGauge(void);
void Area_ClaimSpawnSlot(void);
s32  Area_StepSpawnSlots(void);
void Area_DrawSpawnSlot(AreaSpawnSlot* slot);
void Area_FinishTurnStep(void);
s32  Area_BeginTurnStep(s32 direction, s32 previous);

#endif
