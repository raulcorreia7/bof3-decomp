#ifndef OVERLAY_SCENARIO_SCENA14_00_H
#define OVERLAY_SCENARIO_SCENA14_00_H

/* The scenario/scena14/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "engine/game/00/game_00.h"

extern u8 D_80144908[];

extern u8 D_80144F5F;

extern u8 D_80145FF4;
extern u8 D_80146134;

/* kept: written as g_SceneState.flags_01, func_801F8850 changes size and the image symbols move. */
extern u8 D_80146871;
extern u8 D_80146874;

extern u8       D_80146875;
extern s32      g_AreaFocusY;
extern u16      D_80147A96;
extern u32      D_801F6C00;
extern Callback D_801FC418[];
extern Callback D_801FC424[];

extern s8        D_801FC44C[];
/* D_801FC468 */
extern SceneFunc g_SceneActorDispatch[];

#endif
