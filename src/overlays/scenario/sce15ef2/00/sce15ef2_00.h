#ifndef OVERLAY_SCENARIO_SCE15EF2_00_H
#define OVERLAY_SCENARIO_SCE15EF2_00_H

/* The scenario/sce15ef2/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"

/* The 16 six-byte effect slots. */
#define SCENE_SLOT_BASE AREA_WORK_WINDOW

extern u32      D_801D0C00;
extern Callback D_801D1B2C[];
extern Callback D_801D1B48[];

s32 func_801D1624(s32 countdown);

#endif
