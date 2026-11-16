#ifndef OVERLAY_WORLD03_AREA140_13_H
#define OVERLAY_WORLD03_AREA140_13_H

/* The world03/area140/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/world03.h"
#include "area/spad.h"
#include "game/spawn.h"

typedef struct Area140InputSnapshot {
    u16 buttons;
} Area140InputSnapshot;

ASSERT_SIZE(Area140InputSnapshot, 0x02);

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */
/* The shared flag word the release path clears a bit of. */
/* The request selector and the bytes the cancel path sets. */

/* The state handler tables the dispatchers index. */
extern u8       D_801F47C4[];
extern Callback D_801F47DC[];
extern Callback D_801F4AC4[];

/* The overlay step the timer enters. */
void func_801F3050(void);

s32 func_801F3C44(s32 x, s32 y);

void func_801F3950(s32 arg0, s32 arg1);

/* A start cell and the way the actor faces from it. */
typedef struct AreaStart {
    u8 x;
    u8 y;
    u8 direction;
    u8 param;
} AreaStart;

extern AreaStart D_801F47F4[];

s32 func_801F4058(s16 x, s16 y);

void func_801F4380(u16 x, u16 y);

/* The x step of each facing in the resident facing table, and the y step as the
 * second byte. */
extern u8 D_80181B00[];
extern u8 D_80181B01[];

/* The script index and the mirror flag of each facing pair, read by func_801F3E30. */
extern u8 D_801F4A6C[];
extern u8 D_801F4A6D[];

#endif
