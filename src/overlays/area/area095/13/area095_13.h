#ifndef OVERLAY_WORLD02_AREA095_13_H
#define OVERLAY_WORLD02_AREA095_13_H

/* The world02/area095/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8 D_801F3684[];
/* The cell rows the floor quad walk reads: x, y and the signed depth of each. */
extern u8 D_801F3694[];
extern u8 D_801F3695[];
extern s8 D_801F3696[];

/* The quad part word: the tag in the high half, the tile in the low half. */
#define AREA095_QUAD_PART_WORD ((0xB600u << 16) | 0xB102u)

void func_801F2F3C(s32 depth, s32 height);
void func_801F2C48(void);

#endif
