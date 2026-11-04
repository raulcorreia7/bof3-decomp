#ifndef OVERLAY_WORLD01_AREA048_13_H
#define OVERLAY_WORLD01_AREA048_13_H

/* The world01/area048/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_8014686B;
extern u8 D_80145F09;
extern u8 D_80147CC8;
extern u8 D_801F4D68[];
extern u8 D_801F4D80[];
extern u8 D_801F4E54[];
s32       func_801F3AE4(s32, s32, s32);
void      SYS_ToggleFlag(void* bits, u8 bit_index);

extern u8 D_80146874;

extern u8 D_80146875;

#endif
