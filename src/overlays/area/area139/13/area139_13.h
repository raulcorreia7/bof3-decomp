#ifndef OVERLAY_WORLD03_AREA139_13_H
#define OVERLAY_WORLD03_AREA139_13_H

/* The world03/area139/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */
#define g_CurrentActor ((u8*)g_CurrentActor)

/* The party position in 16.16 fixed point. */
/* The state handler tables the dispatchers index. */
extern Callback D_801F4430[];
/* The four cells of the party line: y at one x, x at one y. */
extern u8       D_801F4440[];
extern u8       D_801F4444[];
extern Callback D_801F4448[];

#endif
