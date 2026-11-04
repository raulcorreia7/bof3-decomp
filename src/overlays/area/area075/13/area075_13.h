#ifndef OVERLAY_WORLD01_AREA075_13_H
#define OVERLAY_WORLD01_AREA075_13_H

/* The world01/area075/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern s32      D_80144ED8;
extern s8       D_80146B81;
extern s8       D_80146BF7;
extern s8       D_80146BF8;
extern s16      D_80146BFE;
extern u8       D_801F4FD4[];
extern u8       D_801F5808[];
extern u8       D_801F5810[];
extern u8       D_801F5818[];
extern Callback D_801F5820[];
extern u8       D_801F58C0;
extern u8       D_801F58D0;
extern u8       D_801F58D1;
extern u8       D_801F58C6;
extern u8       D_801F58C7;
extern u8       D_801F58C8;
extern u8       D_801F58D2;
extern u8       D_801F58D3;
extern u16      D_801F58CA;
extern u16      D_801F58CC;

extern void func_801F4874(void);

#endif
