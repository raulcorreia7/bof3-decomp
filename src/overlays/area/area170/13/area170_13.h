#ifndef OVERLAY_WORLD04_AREA170_13_H
#define OVERLAY_WORLD04_AREA170_13_H

/* The world04/area170/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The scratchpad cell holding this mode's work pointer. */

/* The overlay's flag word. */

/* The game-overlay state bytes the request writes. */

/* The shared game work word the flag mask sets. */

/* The party position in 16.16 fixed point. */
extern s32 D_80145EC4;
/* The payload includes the per-state handler tables. */
extern u8  D_801F57BC[];

extern void func_801F3994(void);

#endif
