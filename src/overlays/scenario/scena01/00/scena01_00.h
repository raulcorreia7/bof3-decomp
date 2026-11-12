#ifndef OVERLAY_SCENARIO_SCENA01_00_H
#define OVERLAY_SCENARIO_SCENA01_00_H

/* The scenario/scena01/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "area/spad.h"
#include "shared/AreaSpark.h"

extern u8 D_80144E90[];

extern u8 D_80146865;

extern u8 D_80146866;

extern u8 D_80146874;

extern u8        D_80146875;
extern u32       D_801F6C00;
extern Callback  D_801FE26C[];
extern Callback  D_801FE29C[];
extern Callback  D_801FE2A8[];
extern SceneFunc D_801FE308[66];

extern u8 D_801FE350;
extern s8 (*D_801FE35C[])(void);

u8 func_801F7C54(void);

void func_801F7678(s32 arg0);
void func_801F7AE4(void);

void func_801F7DCC(s32 red, s32 green, s32 blue);
void func_801F7EDC(void);

#endif
