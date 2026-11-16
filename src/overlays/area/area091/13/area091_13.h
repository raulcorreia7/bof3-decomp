#ifndef OVERLAY_WORLD02_AREA091_13_H
#define OVERLAY_WORLD02_AREA091_13_H

/* The world02/area091/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

/* The master's agility terms and his answers. */
#define AREA091_MSG_AGILITY_TERMS   0x5
#define AREA091_MSG_ITEM_MISSING    0x6
#define AREA091_MSG_MASTER_FAREWELL 0x7

extern Callback D_801F3B44[];

void func_801F2ED4(u16 radius, u16 color);

#endif
