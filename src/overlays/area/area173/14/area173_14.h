#ifndef OVERLAY_WORLD04_AREA173_14_H
#define OVERLAY_WORLD04_AREA173_14_H

/* The world04/area173/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The current work record and its second halfword table. */

/* The scratchpad cell holding this mode's work pointer. */

/* The cell a state lands on, in tile units. */
typedef struct CellOffset {
    u8 x;
    u8 y;
} CellOffset;

/* The payload's first words: the per-state handler pointers. */
extern u8                  D_801F4ED4[];
extern CellOffset          D_801F5304[];
extern u8                  D_801F5308[];
/* D_801F5914 */
extern PartyMemberMessages g_PartyMemberMessages[2];

/* The mode byte the request handler writes. */

void func_801F3954(s32 arg0);
void func_801F3FBC(s32 mode, s32 value);

void func_801F3060(s32 arg0, s32 arg1);
void func_801F3324(s32 source_y, s32 dest_y);

/* Steps the cycling frame timer and copies the frame row at table offset to dest_y every sixth tick. */
#define AREA_CYCLE_FRAME(offset, dest_y)                                 \
    g_Task->timer++;                                                     \
    if (g_Task->timer % 6 == 0) {                                        \
        g_Task->timer = (g_Task->timer < 24) ? g_Task->timer : 0;        \
        func_801F3324(D_801F4ED4[(offset) + g_Task->timer / 6], dest_y); \
    }

/* Sweeps the three func_801F3954 frames by the step timer and moves to the next step after limit ticks. */
#define AREA_SWEEP_STEP(limit)      \
    s16* slot;                      \
    u8   x;                         \
                                    \
    slot       = &D_1F800038;       \
    x          = g_Task->timer;     \
    D_1F80003A = 0;                 \
    *slot      = -(x * 8);          \
    func_801F3954(0);               \
    *slot = g_Task->timer * 8;      \
    func_801F3954(1);               \
    *slot = 0;                      \
    func_801F3954(2);               \
    g_Task->timer += 1;             \
    if (g_Task->timer >= (limit)) { \
        g_Task->timer = 0;          \
        g_Task->header.step += 1;   \
    }

#endif
