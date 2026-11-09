#ifndef OVERLAY_WORLD04_AREA168_13_H
#define OVERLAY_WORLD04_AREA168_13_H

/* The world04/area168/13 overlay: one file per split function and its data. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* Message ids of the card-key door: its ID check result. */
enum {
    AREA168_MESSAGE_ID_CHECK_PASSED = 6,
    AREA168_MESSAGE_ID_CHECK_FAILED = 7,
};

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The shadow-quad renderer the step pairs call; func_801F4158 in the retail symbol map. */
void               func_801F4158_area168(s32 index, s8 code);
/* The cell-code write, taking the three values as full words (this image passes the table words unnarrowed). */
void               func_801A4BC0(s32 column, s32 row, s32 code);
/* The scratchpad quad the shadow pass fills and the GTE reads. */
extern SVECTOR     D_1F800014[];
/* The shadow spread multiplier this pass indexes by the step code. */
extern volatile u8 D_801F4BB4;
/* The two step tables this pass indexes by the menu selection. */
extern u8          D_801F4F94[];
extern u8          D_801F4F95[];

/* The scratchpad cell holding this mode's work pointer. */

/* The party position in 16.16 fixed point. */
/* One cell of the entry tables inside the payload blob. */
#define AREA168_ENTRY_TABLE(type, offset, index) (*(type*)&D_801F4B2C[(offset) + (index)])
/* The payload's data after the last function; the per-state handler tables start at 0xC. */
extern u8 D_801F4B2C[];
extern u8 D_801F4B30[];

/* The game-overlay state bytes the cancel path resets. */
#endif
