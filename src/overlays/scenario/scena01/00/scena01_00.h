#ifndef OVERLAY_SCENARIO_SCENA01_00_H
#define OVERLAY_SCENARIO_SCENA01_00_H

/* The scenario/scena01/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "sys/exe.h"
#include "area/spad.h"
#include "area/effects.h"

extern u8 D_80144E90[];

extern u8 D_80146871;

extern u32                D_801F6C00;
extern Callback           D_801FE26C[];
extern u8                 D_801FE280[];
extern Callback           D_801FE29C[];
extern Callback           D_801FE2A8[];
extern SceneActorCallback D_801FE308[66];

extern u8 D_801FE350;
extern s8 (*D_801FE35C[])(void);
extern Callback jtbl_801F70DC[6];

u8 func_801F7C54(void);

void func_801F7678(s32 arg0);
/* func_801F7AE4 */
void Area_AddSpark(void);

void func_801FD28C(s32 variant);

void func_801F7DCC(s32 red, s32 green, s32 blue);
void func_801F7EDC(void);

#endif
