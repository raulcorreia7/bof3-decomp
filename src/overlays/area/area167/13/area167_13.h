#ifndef OVERLAY_WORLD04_AREA167_13_H
#define OVERLAY_WORLD04_AREA167_13_H

/* The world04/area167/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The scratchpad cell holding this mode's work pointer. */

/* The party position in 16.16 fixed point. */
extern s32 D_80145EC4;
/* The mode byte the request handler writes. */
/* The overlay state bytes the request sets. */
/* The second field focus coordinate the work-position copy reads. */
/* D_80147A90 */
extern s32 g_AreaFocusY;
/* The overlay's flag word. */
/* The payload includes per-state handler tables. */
extern u8  D_801F4A68[];
extern s8  D_80146866;

void SYS_ToggleFlag(void* bits, u8 bit_index);

#endif
