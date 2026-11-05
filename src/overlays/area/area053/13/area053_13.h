#ifndef OVERLAY_WORLD01_AREA053_13_H
#define OVERLAY_WORLD01_AREA053_13_H

/* The world01/area053/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

#define AREA_SELECTION_FIRST  D_801F363C
#define AREA_SELECTION_SECOND D_801F363D

void Area_SetCellCode(s16 column, s16 row, u8 code);

extern u8 D_801F363C[];
extern u8 D_801F363D[];

#endif
