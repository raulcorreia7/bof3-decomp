#ifndef OVERLAY_WORLD03_AREA147_13_H
#define OVERLAY_WORLD03_AREA147_13_H

/* The world03/area147/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

void Area_Update(s32 arg);

/* The global state byte the area update gates on. */

/* The party position in 16.16 fixed point. */
/* The state handler tables the dispatchers index. */
extern u8 D_801F358C[];
extern u8 D_801F35A0[];
extern u8 D_801F35B0[];

/* The payload func_801F2C48 steps by: x and y cell bytes, the z and screen-x
 * words, and the unk_32 byte indexed by the x cell alone. */
extern u8 D_801F35C0[];
extern u8 D_801F35D0[];

#endif
