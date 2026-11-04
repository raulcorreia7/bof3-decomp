#ifndef OVERLAY_WORLD01_AREA047_13_H
#define OVERLAY_WORLD01_AREA047_13_H

/* The world01/area047/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_801F39C8[];

/* The work window's byte table: 16 rows of 0x18 bytes, the in-use byte at +0x14. */
#define AREA_ROW_COUNT       16
#define AREA_ROW_STRIDE      0x18
#define AREA_ROW_FLAG_OFFSET 0x14

#endif
