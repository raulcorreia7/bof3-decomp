#ifndef OVERLAY_WORLD04_AREA157_13_H
#define OVERLAY_WORLD04_AREA157_13_H

/* The world04/area157/13 overlay: one file per split function and its data. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x20
#define ACTOR_SCREEN_X_THRESHOLD 0x100

/* The scratchpad cell holding this mode's work pointer. */

/* The party position in 16.16 fixed point. */
/* The payload's first words: the per-state handler pointers. */
extern u8 D_801F38CC[];
extern u8 D_801F3924[];

/* The target's final handler. */
#endif
