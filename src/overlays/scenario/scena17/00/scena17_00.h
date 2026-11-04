#ifndef OVERLAY_SCENARIO_SCENA17_00_H
#define OVERLAY_SCENARIO_SCENA17_00_H

/* The scenario/scena17/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

extern s8        D_80146873;
extern u8        D_80146874;
u8               func_801F938C(void);
extern u8        D_80146875;
extern u32       D_801F6C00;
extern Callback  D_801F9748[];
extern Callback  D_801F97A4[];
extern SceneFunc D_801F97D8[];

/* func_801D0EA0 */
void Shop_DispatchStep(void);
void func_801F9490(void);
void func_801F88CC(s32 a0, s32 a1);

extern Callback D_801F973C[];

extern u8 D_80146865;
extern u8 D_80146866;
extern u8 D_80146867;

#endif
