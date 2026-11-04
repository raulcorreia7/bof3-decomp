#ifndef OVERLAY_WORLD01_AREA052_13_H
#define OVERLAY_WORLD01_AREA052_13_H

/* The world01/area052/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET 0x15
#define SCRATCH_ROW_STRIDE 0x18

extern u8 D_801F44B8[];
s32       func_801F31C0();
void      func_801F431C(void);

void func_801F3C4C(s32 x, s32 y);

#endif
