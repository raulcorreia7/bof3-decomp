#ifndef OVERLAY_WORLD03_AREA140_13_H
#define OVERLAY_WORLD03_AREA140_13_H

/* The world03/area140/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "work/actor.h"
#include "overlays/area/world03.h"
#include "work/area_spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */
/* The shared flag word the release path clears a bit of. */
/* The request selector and the bytes the cancel path sets. */

/* The state handler tables the dispatchers index. */
extern u8       D_801F47C4[];
extern Callback D_801F47DC[];
extern Callback D_801F4AC4[];

/* The overlay step the timer enters. */
void func_801F3050(void);

s32 func_801F3C44(s32 x, s32 y);

#endif
