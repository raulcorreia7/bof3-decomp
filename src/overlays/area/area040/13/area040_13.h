#ifndef OVERLAY_WORLD01_AREA040_13_H
#define OVERLAY_WORLD01_AREA040_13_H

/* The world01/area040/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

/* The game-overlay state bytes the cancel path resets. */

extern u8 D_80144EA8[];
s32       func_801F2E78(void);

extern u8 D_801F4970[];

extern u8 D_80146875;

#endif
