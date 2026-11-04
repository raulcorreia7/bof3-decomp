#ifndef OVERLAY_SCENARIO_SCENA07_00_H
#define OVERLAY_SCENARIO_SCENA07_00_H

/* The scenario/scena07/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "work/area_spad.h"
#define SCRATCH_ROW_STRIDE 0x1C
#define SCRATCH_ROW_OFFSET 0x00

void             func_801F3C3C(s32 arg0);
extern s8        D_80144EC0;
extern u32       D_801F6C00;
extern Callback  D_801FDD3C[];
extern Callback  D_801FDD48[];
extern Callback  D_801FDD50[];
extern Callback  D_801FDD70[];
extern Callback  D_801FDD8C[];
extern Callback  D_801FDDAC[];
extern Callback  D_801FDDB4[];
extern Callback  D_801FDDC0[];
extern Callback  D_801FDDC8[];
extern Callback  D_801FDDD0[];
extern Callback  D_801FDE10[];
extern Callback  D_801FDE1C[];
extern SceneFunc D_801FDF8C[];
extern u8        D_801FDFC4;
extern u8        D_801FDFC8;

void func_801F8358(void);
s32  func_801F85D8(void);
s32  func_801F9EFC(void);

extern Callback D_801FDD14[];

#endif
