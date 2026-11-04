#ifndef OVERLAY_SCENARIO_SCE15EF2_00_H
#define OVERLAY_SCENARIO_SCE15EF2_00_H

/* The scenario/sce15ef2/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"

#define g_ScanBars ((ScanBar*)AREA_WORK)

extern u32      D_801D0C00;
extern Callback D_801D1B2C[];
extern Callback D_801D1B48[];

/* func_801D1624 */
s32 Scene_StepScanBars(s32 y);

#endif
