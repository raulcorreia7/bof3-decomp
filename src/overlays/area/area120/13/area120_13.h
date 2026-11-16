#ifndef OVERLAY_WORLD03_AREA120_13_H
#define OVERLAY_WORLD03_AREA120_13_H

/* The world03/area120/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "sys/actor.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

extern u8 D_801F43B8[];

/* The width and height halves of the RECT at the start of D_801F43B8. */
extern u16 D_801F43BC;
extern u16 D_801F43BE;

void func_801F35B8(void);
u8   func_801F36B0(void);

extern u8 D_801F43E4;

extern u16 D_801F4FD4;

/* The work window's rows: a byte table of 0x1C-byte rows. */
#define AREA_ROW_COUNT  0x100
#define AREA_ROW_STRIDE 0x1C

/* One row of the work window the field effects step: its active, timer and
 * state bytes, then the 16.16 position the steps move. */
typedef struct AreaRow {
    u8  active;    /* 0x00 nonzero while the row is in use */
    u8  timer;     /* 0x01 counts down to the next state */
    u8  state;     /* 0x02 step index */
    u8  side;      /* 0x03 selects the direction */
    s32 speed;     /* 0x04 16.16 speed */
    u16 angle;     /* 0x08 direction, 0x1000 per turn */
    u16 unk_0A;    /* 0x0A */
    s32 x;         /* 0x0C 16.16 x */
    s32 z;         /* 0x10 16.16 z */
    s32 y;         /* 0x14 16.16 y */
    u8  unk_18[4]; /* 0x18 */
} AreaRow;

ASSERT_OFFSET(AreaRow, active, 0x00);
ASSERT_OFFSET(AreaRow, timer, 0x01);
ASSERT_OFFSET(AreaRow, state, 0x02);
ASSERT_OFFSET(AreaRow, side, 0x03);
ASSERT_OFFSET(AreaRow, speed, 0x04);
ASSERT_OFFSET(AreaRow, angle, 0x08);
ASSERT_OFFSET(AreaRow, x, 0x0C);
ASSERT_OFFSET(AreaRow, z, 0x10);
ASSERT_OFFSET(AreaRow, y, 0x14);
ASSERT_SIZE(AreaRow, AREA_ROW_STRIDE);

/* One rising tile in the area work window: a screen position, a growth step clipped by
 * the height table, and an RGB555 colour the state nibble brightens. */
typedef struct AreaRiseTile {
    u8  flags; /* 0x00 bit 0 active, bits 4-7 state */
    u8  timer; /* 0x01 counts down to the next state */
    u16 color; /* 0x02 RGB555 */
    u16 x;     /* 0x04 */
    u16 y;     /* 0x06 */
    u16 step;  /* 0x08 grows by 2 each frame */
    s16 limit; /* 0x0A index into D_801F4F34 */
} AreaRiseTile;

ASSERT_OFFSET(AreaRiseTile, timer, 0x01);
ASSERT_OFFSET(AreaRiseTile, color, 0x02);
ASSERT_OFFSET(AreaRiseTile, x, 0x04);
ASSERT_OFFSET(AreaRiseTile, y, 0x06);
ASSERT_OFFSET(AreaRiseTile, step, 0x08);
ASSERT_OFFSET(AreaRiseTile, limit, 0x0A);
ASSERT_SIZE(AreaRiseTile, 0x0C);

/* The height limit of each rising tile, by the row's limit index. */
extern s16 D_801F4F34[];

/* Queues the row's sprite at its 16.16 position. */
void func_801F3468(AreaRow* row);

/* g_GameEntryState and the byte after it, read as one word. */
extern u32 g_GameEntryStateWord;
extern u8  D_801EB748[];
extern u8  D_801F4404[];
extern u8  D_801F4405[];

void func_801F3630(void);

void func_801F3F5C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif
