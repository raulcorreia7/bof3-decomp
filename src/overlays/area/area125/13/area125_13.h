#ifndef OVERLAY_WORLD03_AREA125_13_H
#define OVERLAY_WORLD03_AREA125_13_H

/* The world03/area125/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET   0x00
#define SCRATCH_ROW_STRIDE   0x28

/* The row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT 16

extern u8 D_801F364C[];
extern u8 D_801F364E[];
extern u8 D_801F368C[];
extern u8 D_801F368E[];
extern u8 D_801F36F0[];
extern u8 D_801F36F8[];
extern u8 D_801F3834;

void func_801F31B0(s32 slot);
s32  func_801F33B0(void);

void func_801F3268(u8 count);

#endif
