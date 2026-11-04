#ifndef OVERLAY_WORLD04_AREA174_13_H
#define OVERLAY_WORLD04_AREA174_13_H

/* The world04/area174/13 overlay: one file per split function
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
/* The payload's first words: the per-state handler pointers. */
extern u8  D_801F4FAC[];

extern u8   func_801F2EC4(void);
extern void func_801F4B0C(void);
extern void func_801F4C68(void);

u8* func_801F2E88(void);

#endif
