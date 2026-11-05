#ifndef OVERLAY_WORLD03_AREA147_13_H
#define OVERLAY_WORLD03_AREA147_13_H

/* The world03/area147/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

void Area_Update(s32 arg);

/* The global state byte the area update gates on. */

/* The party position in 16.16 fixed point. */
extern s32 D_80145EC4;
/* The state handler tables the dispatchers index. */
extern u8  D_801F358C[];

#endif
