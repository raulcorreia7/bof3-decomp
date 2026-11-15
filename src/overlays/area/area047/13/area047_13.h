#ifndef OVERLAY_WORLD01_AREA047_13_H
#define OVERLAY_WORLD01_AREA047_13_H

/* The world01/area047/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

extern s32 D_80145ECC;
extern u8  D_801F39C8[];

/* The work window's sixteen rows, as the byte walks read them. */
#define AREA_ROW_COUNT       16
#define AREA_ROW_STRIDE      0x18
#define AREA_ROW_FLAG_OFFSET 0x14

/* One row of the work window: the ring the overlay leaves at the lead
 * member's position, its two projected sizes and the grey both ring passes
 * draw with. func_801F2F60 reads +0x10 and +0x12 as signed halfwords and +0x17
 * as the grey. */
typedef struct AreaRingRow {
    WorldPos pos;        /* 0x00 */
    s32      unk_0C;     /* 0x0C */
    s16      size;       /* 0x10 the size both ring passes project from */
    s16      size_delta; /* 0x12 what the second ring pass takes off the size */
    u8       active;     /* 0x14 nonzero while the row is in use */
    u8       stage;      /* 0x15 the row's trail stage */
    u8       timer;      /* 0x16 frames left; clears active at 0 */
    u8       shade;      /* 0x17 the grey both ring passes draw with */
} AreaRingRow;

ASSERT_OFFSET(AreaRingRow, pos, 0x00);
ASSERT_OFFSET(AreaRingRow, size, 0x10);
ASSERT_OFFSET(AreaRingRow, active, 0x14);
ASSERT_OFFSET(AreaRingRow, shade, 0x17);
ASSERT_SIZE(AreaRingRow, 0x18);

void func_801F2DB4(s32* pos, s16 radius, u8 center_shade, u8 rim_shade);

void func_801F2F60(AreaRingRow* row);

void func_801F31F4(s16 scale);

void func_801F32C4(void);

u8 func_801F330C(void);

void func_801F3298(void);

extern s16 D_801492DC;

#endif
