#ifndef OVERLAY_WORLD01_AREA048_13_H
#define OVERLAY_WORLD01_AREA048_13_H

/* The world01/area048/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

extern u8 D_8014686B;
extern u8 D_80146874;
extern u8 D_80146875;
extern u8 D_80147CC8;
/* The disc's colour rows: one byte table per channel, indexed by the work record's byte 6. */
extern u8 D_801F4D5C[];
extern u8 D_801F4D5D[];
extern u8 D_801F4D5E[];
extern u8 D_801F4D68[];
s32       func_801F3AE4(s32, s32, s32);

extern u8 D_801F4D80[];

extern u8 D_801F4E54[];
extern u8 D_801F4E6C[];
extern u8 D_801F4E70[];
extern u8 D_801F4E74[];

s32  func_801F4C28(s32 x, s32 y);
void func_801F2EC0(void);
void func_801F41F0(s32 page, s32 column);

void func_801F302C(void* arg0, void* arg1, void* arg2);
void func_801F4258(s32 arg0);

#endif
