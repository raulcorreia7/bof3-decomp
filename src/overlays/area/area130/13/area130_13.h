#ifndef OVERLAY_WORLD03_AREA130_13_H
#define OVERLAY_WORLD03_AREA130_13_H

/* The world03/area130/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

#include "shared/WorldSpin.h"

#include <string.h>

#define AREA_SPIN_RADIUS     32
#define AREA_SPIN_PITCH      RANDOM_MASK(0x3FF)
#define AREA_SPIN_SCALE_MASK 0x7
#define AREA_SPIN_SCALE_BASE 8
#define AREA_SPIN_FADE       0

extern u8  D_80144F5B;
extern u8  D_80144F5C;
extern u8  D_80145FD0;
extern s16 D_80145FFE;
extern s16 D_80146000;
extern u8  D_80146110;
extern s16 D_8014613E;
extern s16 D_80146140;
extern u8  D_801F3ED8[];
extern u16 D_801F5058[];
extern u16 D_801469EA;

void func_801F3400(s16 x, s16 y, s16 z, s16 w);

bool Item_Add(s32 category, u8 item, u8 amount, s32 unused);

#endif
