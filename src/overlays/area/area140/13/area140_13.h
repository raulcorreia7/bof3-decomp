#ifndef OVERLAY_WORLD03_AREA140_13_H
#define OVERLAY_WORLD03_AREA140_13_H

/* The world03/area140/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/worlds/world03.h"
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

/* The four corner offsets (x, y, z) of each quad shape, biased by 0x80 in x and y. */
extern s8  D_801F4800[][4][3];
/* The six quads of each facing: cell x and y step, shape and tile column. */
extern u8  D_801F4824[][6][4];
/* The base height of each facing's quads. */
extern u16 D_801F4854[];
/* The tile row of each quad shape. */
extern u8  D_801F4858[];

/* Draws the six semi-transparent quads of a facing around the task, lowered by height. */
void func_801F3950(s32 facing, s32 height);

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

/* The x step of each facing in the resident facing table, and the y step as the
 * second byte. */
extern u8 D_80181B00[][2];

/* The script index and the mirror flag of each facing pair, read by func_801F3E30. */
extern u8 D_801F4A6C[];
extern u8 D_801F4A6D[];

/* A cell and facing that sets a scene flag, recolours the cell and may spawn its effect or wait for the party. */
typedef struct Area140Trigger {
    u8 x;
    u8 y;
    u8 facing;
    u8 flag;
    u8 spawn; /* nonzero spawns the effect actor on the cell */
    u8 type;  /* nonzero indexes D_801F4AB4: the cell the party must leave first */
} Area140Trigger;

ASSERT_SIZE(Area140Trigger, 0x06);

/* The cell a party member's projected position must not touch. */
typedef struct Area140Cell {
    u16 x;
    u16 y;
} Area140Cell;

ASSERT_SIZE(Area140Cell, 0x04);

/* The trigger cell count func_801F4380 walks. */
#define AREA140_TRIGGER_COUNT 8

extern Area140Trigger D_801F4A84[AREA140_TRIGGER_COUNT];
extern Area140Cell    D_801F4AB4[];

#endif
