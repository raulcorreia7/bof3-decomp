#ifndef OVERLAY_WORLD01_AREA047_13_H
#define OVERLAY_WORLD01_AREA047_13_H

/* The world01/area047/13 overlay: one file per split function and its data. */

#include "overlays/area/world01.h"

extern s32 D_80145ECC;
extern u8  D_801F39C8[];

/* The work window's byte table: 16 rows of 0x18 bytes, the in-use byte at +0x14. */
#define AREA_ROW_COUNT       16
#define AREA_ROW_STRIDE      0x18
#define AREA_ROW_FLAG_OFFSET 0x14

void func_801F31F4(s16 scale);

void func_801F32C4(void);

void func_801F330C(void);

void func_801F3298(void);

extern s16 D_801492DC;

#endif
