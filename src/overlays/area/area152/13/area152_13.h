#ifndef OVERLAY_WORLD04_AREA152_13_H
#define OVERLAY_WORLD04_AREA152_13_H

/* The world04/area152/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"
#include "common/util.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The scratchpad cell holding this mode's work pointer. */

extern SVECTOR D_1F800014[];
/* The selection byte that arms the area request. */
/* The area state byte and the frame flags it is tested against. */
/* The staged cue rows' fields: the allocation flags, kind, layer, step and
 * distance halfword, indexed by the row stride the spawn pass allocates. */
/* The payload's data after the last function; the per-state handler tables
 * start at 0x130. */
extern u8      D_801F4C3C[];
#define AREA_HUD_SPRITE_CELLS (D_801F4C3C + 0x158)
/* D_801F4E10 */
extern Point2u g_FlockVelocity[4];
/* D_801F4E20 */
extern u8      g_FlockScript[4][2];

/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F4DEC[6];
#define AREA_HUD_MASK_TABLE D_801F4DEC

void func_801F338C(void);

void func_801F3550(void);

#include "overlays/area/world_cloud.h"

#endif
