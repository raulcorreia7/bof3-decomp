#ifndef OVERLAY_WORLD04_AREA173_14_H
#define OVERLAY_WORLD04_AREA173_14_H

/* The world04/area173/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "work/area_spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The current work record and its second halfword table. */

/* The scratchpad cell holding this mode's work pointer. */

/* The payload's first words: the per-state handler pointers. */
extern u8                  D_801F4ED4[];
/* D_801F5914 */
extern PartyMemberMessages g_PartyMemberMessages[2];

/* The mode byte the request handler writes. */

void func_801F3954(s32 arg0);
void func_801F3FBC(s32 mode, s32 value);

#endif
