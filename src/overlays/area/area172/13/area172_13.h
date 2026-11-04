#ifndef OVERLAY_WORLD04_AREA172_13_H
#define OVERLAY_WORLD04_AREA172_13_H

/* The world04/area172/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"
#include "shared/WorldSpin.h"

#define AREA_SPIN_RADIUS     24
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x3
#define AREA_SPIN_SCALE_BASE 4
#define AREA_SPIN_FADE       0

/* The scratchpad cell holding this mode's work pointer. */

/* The payload's first words: the per-state handler pointers. */
extern u8 D_801F507C[];

/* The overlay's flag word. */

extern void Area_SetCellCode(s16 column, s16 row, u8 code);
extern void func_801F2DF4(s32 arg0);
void        func_801F4E8C(s32 x, s32 y);

extern u8 D_80146874;

extern u8 D_80146875;

extern u8 D_80144EF8[];

#endif
