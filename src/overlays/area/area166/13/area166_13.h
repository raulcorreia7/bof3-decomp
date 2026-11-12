#ifndef OVERLAY_WORLD04_AREA166_13_H
#define OVERLAY_WORLD04_AREA166_13_H

/* The world04/area166/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The party position in 16.16 fixed point. */
/* The scratchpad cell holding this mode's work pointer. */
/* The payload's first words: the per-state handler pointers and its entry coordinate pairs. */
extern u8 D_801F3718[];
/* The two step tables this pass indexes by the menu selection. */
extern u8 D_801F3940[];
extern u8 D_801F3941[];

/* The destination x and y byte pairs this pass indexes by the current x cell. */
extern u8 D_801F3748[][2];

/* The game-overlay state bytes the cancel path resets. */

/* The overlay's frame handler. */
#endif
