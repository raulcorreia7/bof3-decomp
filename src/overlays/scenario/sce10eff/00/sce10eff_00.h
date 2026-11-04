#ifndef OVERLAY_SCENARIO_SCE10EFF_00_H
#define OVERLAY_SCENARIO_SCE10EFF_00_H

/* The scratchpad base here is the 32-bit depth word. */
#define GAME_SCRATCH_BASE_WORD
#include "overlays/scenario/scenario.h"
#include "sys/gameui.h"

/* rsin/rcos take 4096 (ONE) units per turn: the orbit counter wraps every 128
 * steps of 32 units. */
#define SCE10EFF_ORBIT_STEPS          128
#define SCE10EFF_ORBIT_STEP_SHIFT     5
#define SCN_EFFECT_STATE_STEP_COUNT   15
#define SCE10EFF_ORBIT_ANGLE(counter) (((counter) & (SCE10EFF_ORBIT_STEPS - 1)) << SCE10EFF_ORBIT_STEP_SHIFT)
#define g_SpadWork                    ((SceneBandEffect*)g_SpadWork)

/* Project the orbit step into the scratchpad pair and advance the position. A
 * bare statement macro: the member declares `work`, `counter`, `angle`,
 * `angle_cell` and `velocity`. Kept: as an inline the frame shrinks 4 bytes
 * (ra at 16(sp), retail 20(sp)); the do/while form moves bytes. */
#define SCENE_PROJECT_ORBIT_STEP(depth)                            \
    g_SpadWork->ticker++;                                          \
                                                                   \
    work                          = g_SpadWork;                    \
    counter                       = work->orbit_counter + 1;       \
    VOL(s32, work->orbit_counter) = counter;                       \
    angle                         = SCE10EFF_ORBIT_ANGLE(counter); \
    angle_cell                    = &D_1F800004;                   \
    *angle_cell                   = angle;                         \
    D_1F800000                    = (depth);                       \
                                                                   \
    velocity     = rcos(angle) * D_1F800000;                       \
    work         = g_SpadWork;                                     \
    work->proj_x = D_801D2744->proj_x + velocity;                  \
                                                                   \
    velocity           = rsin(*angle_cell) * D_1F800000;           \
    g_SpadWork->proj_y = D_801D2744->proj_y + velocity;            \
                                                                   \
    if (TIMER_EXPIRED(g_SpadWork->timer)) {                        \
        g_SpadWork->step_index++;                                  \
    }

/* Projected scenario bands: func_801D0FAC draws at the source origin;
 * func_801D12A8 places orbiting copies, and Scene_DrawBands draws the bands. */
typedef struct SceneBandEffect {
    u8             pad_00[0x01];
    /* 0x01 */ u8  unk_01;     /* bumped once per record batch */
    /* 0x02 */ u8  state;      /* indexes the D_801D2708 state table */
    /* 0x03 */ u8  step_index; /* indexes the D_801D2714 sub-table; bumped once per step */
    /* 0x04 */ u8  orbit_seed; /* seeds the orbit counter */
    u8             pad_05[0x03];
    /* 0x08 */ u8  flags;
    /* 0x09 */ u8  timer;         /* counts down from 60 */
    /* 0x0A */ u8  band;          /* a band counter, grown by 2 */
    /* 0x0B */ u8  ticker;        /* a random nibble that is bumped */
    /* 0x0C */ s32 orbit_counter; /* the orbit counter */
    u8             pad_10[0x1E];
    /* 0x2E */ u16 origin_x; /* the primitive's x origin */
    /* 0x30 */ u16 origin_y; /* the primitive's y origin */
    u8             pad_32[0x02];
    /* 0x34 */ s32 proj_x; /* the projected x, 16.16 */
    /* 0x38 */ s32 proj_y; /* the projected y, 16.16 */
    u8             pad_3c[0x02];
    /* 0x3E */ s16 proj_z; /* the projected z; the GTE vertex takes it halved */
} SceneBandEffect;

ASSERT_SIZE(SceneBandEffect, 0x40);
ASSERT_OFFSET(SceneBandEffect, state, 0x02);
ASSERT_OFFSET(SceneBandEffect, step_index, 0x03);
ASSERT_OFFSET(SceneBandEffect, orbit_counter, 0x0C);
ASSERT_OFFSET(SceneBandEffect, origin_x, 0x2E);
ASSERT_OFFSET(SceneBandEffect, origin_y, 0x30);
ASSERT_OFFSET(SceneBandEffect, proj_x, 0x34);
ASSERT_OFFSET(SceneBandEffect, proj_y, 0x38);
ASSERT_OFFSET(SceneBandEffect, proj_z, 0x3E);

/* Data, in address order. */
extern s32              D_1F800004;
extern s32              D_1F800008;
extern s32              D_1F80000C;
extern SVECTOR          D_1F800014[];
extern s16              D_1F800016;
extern s16              D_1F800018;
extern Callback         D_801D2708[SCN_EFFECT_STATE_STEP_COUNT];
extern Callback         D_801D2714[];
extern Callback         D_801D2724[];
extern Callback         D_801D2734[];
extern SceneBandEffect* D_801D2744;

void Scene_RunEffect(void);
void Scene_EffectBegin(void);
void Scene_EffectEnd(void);
void Scene_EffectRunState(void);
void Scene_EffectSetMatrix(void);
void func_801D0FAC(void);
void func_801D1034(void);
void func_801D10C8(void);
void func_801D1138(void);
void func_801D11A0(void);
void func_801D1218(void);
void func_801D12A8(void);
void func_801D13C0(void);
void func_801D1430(void);
void func_801D1544(void);
void Scene_DrawBands(s32 band_height, u16 radius, u16 jitter_mask);
void func_801D1D58(void);
void func_801D1DE0(void);
void func_801D1EFC(void);
void func_801D1F50(void);
void func_801D2064(void);
void func_801D218C(void);
void func_801D240C(void);
void func_801D2658(void);

/* Step the scenario band by two and reset the timer at its limit. */
static inline void Scene_AdvanceBand(u32 band_limit) {
    /* A store through the pointer may alias the cell, so each step reloads it. */
    SceneBandEffect* work;

    g_SpadWork->ticker++;
    work = g_SpadWork;
    if (work->band < band_limit) {
        work->band += 2;
    } else {
        work->timer = 60;
        work        = g_SpadWork;
        work->step_index++;
    }
}

#endif
