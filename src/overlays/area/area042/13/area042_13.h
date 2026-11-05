#ifndef OVERLAY_WORLD01_AREA042_13_H
#define OVERLAY_WORLD01_AREA042_13_H

/* The world01/area042/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);
void func_801F37A8(s32 arg0, s32 arg1);

extern u8  D_801F52D0[];
extern u8  D_801F52E8[];
extern u8  D_801F5334[];
extern u16 D_801F56C4[];

void func_801F3D18(s32);

extern u8 D_801F532C[];
extern u8 D_801F534C[];
extern u8 D_80145F09;

#endif
