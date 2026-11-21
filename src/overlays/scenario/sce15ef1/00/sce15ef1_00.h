#ifndef OVERLAY_SCENARIO_SCE15EF1_00_H
#define OVERLAY_SCENARIO_SCE15EF1_00_H

/* The scenario/sce15ef1/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/effects.h"
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

extern AreaSpawnSlot D_801D39A8[EFFECT_SLOT_COUNT];

/* The dot trail: D_801D40A8 points of 10 bytes at AREA_WORK + 0x5A00. */
#define SCENE_DOT_TRAIL MEM_PTR(TrailDot, AREA_WORK + 0x5A00)

extern RECT D_801D393C[];
extern u16  D_801D40A8;
extern u8   D_801D40AC;
extern u32  D_801D40B0;
extern u32  D_801D40B4;

extern SpinEffect g_WorldSpins[];

/* func_801D147C */
void GFX_DrawColorFan(s32* pos, s16 origin, s32 flags);
void func_801D1678(s32* from, s32* to, u8 intensity);
void func_801D36BC(s32* pos, s32 vx, s32 vy);

#endif
