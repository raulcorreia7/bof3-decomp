#ifndef OVERLAY_SCENARIO_SCENA14_00_H
#define OVERLAY_SCENARIO_SCENA14_00_H

/* The scenario/scena14/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/save.h"

extern u16 g_GameAreaId;
extern u8  D_80144908[];
extern u8  D_80144F5E;

extern u8 D_80144F5F;

extern u8 D_80145FF4;
extern u8 D_80146134;

/* kept: written as g_SceneState.flags_01, func_801F8850 changes size and the image symbols move. */
extern u8 D_80146871;
extern u8 D_80146874;

extern u8       D_80146875;
extern u32      D_801F6C00;
extern Callback D_801FC418[];
extern Callback D_801FC424[];

extern s8        D_801FC44C[];
extern SceneFunc D_801FC468[];

#endif
