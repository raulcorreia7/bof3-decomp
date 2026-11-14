#ifndef OVERLAY_SCENARIO_SCE15EF1_00_H
#define OVERLAY_SCENARIO_SCE15EF1_00_H

/* The scenario/sce15ef1/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "shared/CaptureSize.h"
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

/* One 10-byte point of the dot trail at AREA_WORK + 0x5A00. */
typedef struct SceneDot {
    u8  active; /* +0x00 - flips every frame it is processed */
    u8  life;   /* +0x01 */
    u16 color;  /* +0x02 - 5-5-5 */
    s16 x;      /* +0x04 */
    s16 y;      /* +0x06 */
    s8  dx;     /* +0x08 */
    s8  dy;     /* +0x09 */
} SceneDot;

ASSERT_SIZE(SceneDot, 10);

extern CaptureSize D_801D3940[];
extern u16         D_801D40A8;
extern u8          D_801D40AC;
extern u32         D_801D40B0;
extern u32         D_801D40B4;

extern WorldSpin g_WorldSpins[];

void func_801D147C(s32* pos, s16 origin, s32 flags);
void func_801D1678(void* arg0, void* arg1, s32 arg2);
void func_801D36BC(s32* pos, s32 vx, s32 vy);

#endif
