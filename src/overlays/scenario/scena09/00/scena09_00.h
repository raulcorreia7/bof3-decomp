#ifndef OVERLAY_SCENARIO_SCENA09_00_H
#define OVERLAY_SCENARIO_SCENA09_00_H

/* The scenario/scena09/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"

extern u8       D_80144908[];
extern u8       D_80145F09;
extern u8       D_80146865;
extern u8       D_80146866;
extern u8       D_80146867;
extern u8       D_8014623B;
extern u8       D_80146874;
extern u8       D_80146875;
extern u16      D_80146876;
extern u32      D_801F6C00;
extern Callback D_801FE384[];
extern Callback D_801FE3E0[];
extern Callback D_801FE3EC[];
extern u8       D_801FE430[4];

/* func_801F7574 */
void Scene_ClearWorkRows(void);
s32  func_801F75BC(void);
void func_801F76D0(void);

extern SceneFunc D_801FE434[];

#endif
