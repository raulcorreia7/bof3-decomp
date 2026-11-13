#ifndef OVERLAY_WORLD04_AREA169_13_H
#define OVERLAY_WORLD04_AREA169_13_H

/* The world04/area169/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The scratchpad cell holding this mode's work pointer. */

/* The mode byte the handler tests and the overlay's flag word. */
/* The party position in 16.16 fixed point. */
/* The payload's first words: the per-state handler pointers. */
extern u8 D_801F3A90[];

/* The quad's blue level by step, in units of 8. */
extern u8 D_801F3AB0[];

extern TriggerBox D_801F3B9C[2];

/* The target's final handler. */
#endif
