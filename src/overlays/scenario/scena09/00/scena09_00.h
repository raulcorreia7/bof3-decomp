#ifndef OVERLAY_SCENARIO_SCENA09_00_H
#define OVERLAY_SCENARIO_SCENA09_00_H

/* The scenario/scena09/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"

extern u32       D_801F6C00;
extern u8        D_80144908[];
extern Callback  D_801FE3E0[];
extern Callback  D_801FE3EC[];
extern SceneFunc D_801FE434[];

s32  func_801F75BC(void);
void func_801F7574(void);
void func_801F76D0(void);

extern Callback D_801FE384[];

#endif
