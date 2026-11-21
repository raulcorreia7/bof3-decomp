#ifndef OVERLAY_WORLD03_AREA140_13_H
#define OVERLAY_WORLD03_AREA140_13_H

/* The world03/area140/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/worlds/world03.h"
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

void func_801F3950(s32 pos_x, s32 pos_y);

s32 func_801F3C44(s32 x, s32 y);

/* A start cell and the way the actor faces from it. */
typedef struct AreaStart {
    u8 x;
    u8 y;
    u8 facing;
    u8 param;
} AreaStart;

extern AreaStart D_801F47F4[];

bool func_801F4058(s16 x, s16 y);

u8 func_801F4380(s32 x, s32 y);

/* The party proximity check's row count. */
extern u8 D_80146254;

/* The x step of each facing in the resident facing table, and the y step as the
 * second byte. */
extern u8 D_80181B00[];
extern u8 D_80181B01[];

/* The script index and the mirror flag of each facing pair, read by func_801F3E30. */
extern u8 D_801F4A6C[];
extern u8 D_801F4A6D[];

/* The eight trigger rows: cell x, cell y, facing, effect flag, spawn flag and spawn type. */
extern u8 D_801F4A84[];
extern u8 D_801F4A85[];
extern u8 D_801F4A86[];
extern u8 D_801F4A87[];
extern u8 D_801F4A88[];
extern u8 D_801F4A89[];

/* The two projected-position limits of the party proximity check, by spawn type. */
extern u16 D_801F4AB4[];
extern u16 D_801F4AB6[];

#endif
