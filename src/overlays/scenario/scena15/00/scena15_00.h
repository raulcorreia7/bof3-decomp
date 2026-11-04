#ifndef OVERLAY_SCENARIO_SCENA15_00_H
#define OVERLAY_SCENARIO_SCENA15_00_H

/* The scenario/scena15/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"
#include "battle/ram.h"

extern u32       D_801F6C00;
extern Callback  D_801FE590[];
extern Callback  D_801FE5A0[];
extern Callback  D_801FE5B0[];
extern Callback  D_801FE5C0[];
extern Callback  D_801FE5CC[];
extern Callback  D_801FE66C[];
extern Callback  D_801FE678[];
extern SceneFunc D_801FE6EC[];

s32  func_801F7748(void);
void func_801F79C4(void);
void func_801F8704(void);
void func_801F8958(void);
extern u16 g_GameAreaId;
extern u8  D_801FE71C[];
s16        func_801F326C(s32 message);
s16        func_801F37AC(s32 message);

extern Callback D_801FE57C[];

#endif
