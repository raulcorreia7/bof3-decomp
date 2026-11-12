#ifndef OVERLAY_WORLD04_AREA165_13_H
#define OVERLAY_WORLD04_AREA165_13_H

/* The world04/area165/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x20
#define ACTOR_SCREEN_X_THRESHOLD 0x100

/* The party position in 16.16 fixed point. */
/* The scratchpad cell holding this mode's work pointer. */
/* The payload's first words: the per-state handler pointers and its entry coordinate pairs. */
extern u8 D_801F3594[];
/* The destination pair tables the step pass reads. */
extern u8 D_801F35C0[];
extern u8 D_801F35C1[];

/* The overlay's frame handler. */
#endif
