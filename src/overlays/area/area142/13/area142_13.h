#ifndef OVERLAY_WORLD03_AREA142_13_H
#define OVERLAY_WORLD03_AREA142_13_H

/* The world03/area142/13 overlay: one file per split function and its data. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The state handler table the dispatcher indexes. */
extern u8       D_801F3554[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F3B7C[];

/* The step the dispatcher enters with the work timer. */
void func_801F2CB0(s32 timer);

#endif
