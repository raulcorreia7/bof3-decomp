#ifndef OVERLAY_WORLD02_AREA098_13_H
#define OVERLAY_WORLD02_AREA098_13_H

/* The world02/area098/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET    0x00
#define SCRATCH_ROW_STRIDE    0x1C

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_STRIDE 0x18
#define SCRATCH_COLUMN_COUNT  8

#include "shared/WorldSpin.h"

/* One slot of the eight-slot table at the work window: the spawn point's
 * position copied from the scratch record when the slot is claimed. */
typedef struct AreaSpawnSlot {
    u8    active;    /* 0x00 - 0 marks a free slot */
    u8    unk_01;    /* 0x01 */
    u8    unk_02;    /* 0x02 */
    u8    unk_03;    /* 0x03 */
    Coord x;         /* 0x04 */
    Coord y;         /* 0x08 */
    Coord z;         /* 0x0C */
    u8    unk_10[4]; /* 0x10 */
    u16   unk_14;    /* 0x14 */
    u8    unk_16;    /* 0x16 */
    u8    unk_17;    /* 0x17 */
} AreaSpawnSlot;

ASSERT_SIZE(AreaSpawnSlot, 0x18);

#define AREA_SPIN_PRIM_ORDER 2

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x20

extern Callback D_801F5F68[];
extern Callback D_801F5F7C[];
extern Callback D_801F5F88[];
extern Callback D_801F5FAC[];
extern u8       D_801F6510;
extern u8       D_801F6514;

void        Area_ProjectPoint(s32* pos, long* screen_xy);
extern void func_801F526C(void);
extern void func_801F5308(void);
extern void func_801F5940(void);
void        func_801F4D44(void);
void        func_801F5050(u8 level);
void        Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_80146865;

extern u8 D_8014554C[];

#endif
