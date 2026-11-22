#ifndef OVERLAY_SCENARIO_SCENA09_00_H
#define OVERLAY_SCENARIO_SCENA09_00_H

/* The scenario/scena09/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"
#include "area/effects.h"

extern u8  D_80144908[];
extern u8  D_80145F09;
extern u8  D_8014623B;
extern u16 D_80146258;
extern u16 D_8014625A;
extern u32 D_801F6C00;
/* D_801FE384 */

extern TriangleOffset D_801FE38C[];
extern Callback       D_801FE3E0[];
extern Callback       D_801FE3EC[];
extern u8             D_801FE430[4];

#define SCENE_SPARK_COUNT 32

/* func_801F7574 */
void Scene_ClearWorkRows(void);
s32  func_801F75BC(void);
void func_801F76D0(void);

/* D_801FE434 */

extern u8 D_801FE474;
extern s8 (*D_801FE4BC[])(void);
extern u8 D_801FE554;

#endif
