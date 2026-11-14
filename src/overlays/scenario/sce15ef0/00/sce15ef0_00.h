#ifndef OVERLAY_SCENARIO_SCE15EF0_00_H
#define OVERLAY_SCENARIO_SCE15EF0_00_H

/* The scenario/sce15ef0/00 overlay's local declarations. Only this image
 * includes the file. */

#include "common/vector.h"
#include "sys/gameui.h"
#include "overlays/scenario/scenario.h"

#define g_Task ((Sce15ef0Work*)g_Task)

/* The overlay's scratchpad work area: the scenario effect layout (fields at
 * +0x01, +0x09, +0x0C, +0x2E, +0x34 and +0x5D match scena00's SceneEffect). */
typedef struct Sce15ef0Work {
    TaskHeader header;
    u8         pad_03[0x06];
    u8         timer; /* +0x09 */
    u8         pad_0A[0x02];
    s32        counter_0C; /* +0x0C */
    s32        counter_10; /* +0x10 */
    s32        field_14;   /* +0x14 */
    u8         pad_18[0x16];
    u16        origin_x; /* +0x2E */
    u16        origin_y; /* +0x30 */
    u8         pad_32[0x02];
    Point3l    pos;
    u8         pad_40[0x1D];
    u8         color_r; /* +0x5D */
    u8         color_g; /* +0x5E */
} Sce15ef0Work;

ASSERT_SIZE(Sce15ef0Work, 0x60);
ASSERT_OFFSET(Sce15ef0Work, timer, 0x09);
ASSERT_OFFSET(Sce15ef0Work, origin_x, 0x2E);
ASSERT_OFFSET(Sce15ef0Work, pos, 0x34);
ASSERT_OFFSET(Sce15ef0Work, color_r, 0x5D);

extern u32      D_801D0C00;
/* D_801D1F88 */
extern Callback g_SceneEntityDispatch[];

void func_801D1220(s32 value);
void func_801D1914(s16 amount);
void func_801D1A20(s32* pos, s16 origin, s32 flags);
void func_801D1C1C(s32* pos, s32* counter, u8 channel);
#endif
