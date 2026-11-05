#ifndef OVERLAY_SCENARIO_SCE15EF1_00_H
#define OVERLAY_SCENARIO_SCE15EF1_00_H

/* The scenario/sce15ef1/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "shared/WorldSpin.h"
#include "work/area_spad.h"

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
typedef struct EffectSlot {
    u8  active; /* 0x00 */
    u8  unk_01; /* 0x01 */
    u8  life;   /* 0x02 frames left; the update frees the slot at zero */
    u8  pad_03; /* 0x03 */
    s32 x;      /* 0x04 the spawning actor's x, y and z */
    s32 y;      /* 0x08 */
    s32 z;      /* 0x0C */
    s32 unk_10; /* 0x10 */
    u16 size;   /* 0x14 */
    u8  unk_16; /* 0x16 */
    u8  unk_17; /* 0x17 */
} EffectSlot;

ASSERT_SIZE(EffectSlot, 0x18);

#define EFFECT_SLOT_COUNT 16

extern EffectSlot D_801D39A8[EFFECT_SLOT_COUNT];

extern void func_801D1B10(EffectSlot* slot);

extern Callback D_801D3918[];

void Area_ProjectPoint(s32* pos, long* screen_xy);

#endif
