#ifndef OVERLAY_WORLD04_AREA173_14_H
#define OVERLAY_WORLD04_AREA173_14_H

/* The world04/area173/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"
#include <string.h>

/* The map bundle header bytes this overlay reads by their own addresses. */
extern u8  D_80104001;
extern u16 D_80104002;

/* The cell code tables the map update copies: two 6-byte runs in the
 * D_801F2C04 data block. */
extern u8 D_801F2C04[];

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0xC0

/* The per-sprite-row screen scale of the quad's far edge: a signed byte a row. */
#define AREA_ROW_SCALE_OFFSET    0x4C8

/* The current work record and its second halfword table. */

/* The scratchpad cell holding this mode's work pointer. */

/* The cell a state lands on, in tile units. */
typedef Cell2 CellOffset;

/* A part row: the base cell and the four corner cell offsets around it. */
typedef struct AreaPart {
    u8  x;           /* 0x00 */
    u8  y;           /* 0x01 */
    u8  cells[4][3]; /* 0x02 */
    u8  unk_0E[2];   /* 0x0E */
    u32 cell;        /* 0x10 */
} AreaPart;

ASSERT_OFFSET(AreaPart, cells, 0x02);
ASSERT_OFFSET(AreaPart, cell, 0x10);
ASSERT_SIZE(AreaPart, 0x14);

/* The projected quad's origin: x then y. */
extern s16 D_1F800034[2];

/* The part rows: the cell pair, four vertex cells and the part word, 20 bytes each. */
extern AreaPart D_801F4F14[];

/* Each sweep frame's first and last cell row. */
extern u8 D_801F52E8[][2];
extern u8 D_801F52E9[][2];

/* The two boards func_801F3FBC draws: the scroll factor of each mode, the
 * four corner vertex offsets of each of the three runs, and the texture word
 * of each part. */
extern u8    D_801F530C[];
extern Pos3s D_801F5310[3][4];
extern u32   D_801F5358[][2][3];
/* The cell pair a part draw stages, then the drawer's own x and z offsets, as unsigned halfwords. */
extern u16   D_1F800034_U16[4];

/* The payload's first words: the per-state handler pointers. */
extern u8                  D_801F4ED4[];
extern CellOffset          D_801F5304[];
extern u8                  D_801F5308[];
/* D_801F5914 */
extern PartyMemberMessages g_PartyMemberMessages[2];

/* The mode byte the request handler writes. */

void func_801F3954(s32 frame);
void func_801F3FBC(s32 mode, s32 value);

void func_801F3060(s32 index, s32 flag);
void func_801F3324(s32 source_y, s32 dest_y);

/* Steps the cycling frame timer and copies the frame row at table offset to dest_y every sixth tick. */
#define AREA_CYCLE_FRAME(offset, dest_y)                                         \
    SELF(Actor)->timer++;                                                        \
    if (SELF(Actor)->timer % 6 == 0) {                                           \
        SELF(Actor)->timer = (SELF(Actor)->timer < 24) ? SELF(Actor)->timer : 0; \
        func_801F3324(D_801F4ED4[(offset) + SELF(Actor)->timer / 6], dest_y);    \
    }

/* Sweeps the three func_801F3954 frames by the step timer and moves to the next step after limit ticks. */
#define AREA_SWEEP_STEP(limit)           \
    s16* slot;                           \
    u8   x;                              \
                                         \
    slot       = &D_1F800038;            \
    x          = SELF(Actor)->timer;     \
    D_1F80003A = 0;                      \
    *slot      = -(x * 8);               \
    func_801F3954(0);                    \
    *slot = SELF(Actor)->timer * 8;      \
    func_801F3954(1);                    \
    *slot = 0;                           \
    func_801F3954(2);                    \
    SELF(Actor)->timer += 1;             \
    if (SELF(Actor)->timer >= (limit)) { \
        SELF(Actor)->timer = 0;          \
        SELF(Actor)->header.step += 1;   \
    }

#endif
