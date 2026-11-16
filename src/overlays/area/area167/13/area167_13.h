#ifndef OVERLAY_WORLD04_AREA167_13_H
#define OVERLAY_WORLD04_AREA167_13_H

/* The world04/area167/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The game mode the trigger records of this payload match. */
/* The second field focus coordinate the work-position copy reads. */
/* D_80147A90 */
extern s32 g_AreaFocusY;
/* The payload includes per-state handler tables. */
extern u8  D_801F4A68[];
/* Trigger records at the tail of the payload: two match bytes, a mode nibble and a flag bit. */
extern u8  D_801F68B4[];

#define AREA167_ENTRY_TABLE(type, offset, index) AREA_PAYLOAD_FIELD(D_801F4A68, type, offset, index)

#endif
