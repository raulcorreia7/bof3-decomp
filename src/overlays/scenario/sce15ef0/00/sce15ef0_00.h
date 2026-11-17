#ifndef OVERLAY_SCENARIO_SCE15EF0_00_H
#define OVERLAY_SCENARIO_SCE15EF0_00_H

/* The scenario/sce15ef0/00 overlay's local declarations. Only this image
 * includes the file. */

#include "area/spad.h"
#include "common/vector.h"
#include "menu/gameui.h"
#include "overlays/scenario/scenario.h"

extern u32 D_801D0C00;
/* D_801D1F88 */

void func_801D1220(s32 value);
void func_801D1690(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2);
void func_801D1914(s16 amount);
void GFX_DrawColorFan(s32* pos, s16 origin, s32 flags);
void func_801D1C1C(s32* from, s32* to, u8 level);
#endif
