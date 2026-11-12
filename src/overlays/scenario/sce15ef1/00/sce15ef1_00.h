#ifndef OVERLAY_SCENARIO_SCE15EF1_00_H
#define OVERLAY_SCENARIO_SCE15EF1_00_H

/* The scenario/sce15ef1/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "shared/WorldSpin.h"
#include "area/spad.h"

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x40

extern u32      D_801D0C00;
extern Callback D_801D3954[];
extern Callback D_801D396C[];
extern Callback D_801D397C[];

/* One of the sixteen effect slots at D_801D39A8. */
#define EFFECT_SLOT_COUNT 16

/* D_801D3918 */
extern Callback g_SceneEntityDispatch[];

extern AreaSpawnSlot D_801D39A8[EFFECT_SLOT_COUNT];

extern WorldSpin g_WorldSpins[];

void func_801D147C(void* arg0, s32 arg1, s32 arg2);
void func_801D1678(void* arg0, void* arg1, s32 arg2);
void func_801D36BC(s32* pos, s32 vx, s32 vy);

#endif
