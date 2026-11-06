#ifndef OVERLAY_WORLD04_AREA168_13_H
#define OVERLAY_WORLD04_AREA168_13_H

/* The world04/area168/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The shadow-quad renderer the step pairs call; func_801F4158 in the retail
 * symbol map. */
void               func_801F4158_area168(s32 index, s8 code);
/* The two step tables this pass indexes by the menu selection. */
extern u8          D_801F4F94[];
extern u8          D_801F4F95[];
/* The shadow spread multiplier this pass indexes by the step code. */
extern volatile u8 D_801F4BB4;
/* The scratchpad quad the shadow pass fills and the GTE reads. */
extern SVECTOR     D_1F800014[];

/* The scratchpad cell holding this mode's work pointer. */

/* The party position in 16.16 fixed point. */
extern s32 D_80145EC4;
/* The payload's data after the last function; the per-state handler tables
 * start at 0xC. */
extern u8  D_801F4B2C[];

/* The game-overlay state bytes the cancel path resets. */
#endif
