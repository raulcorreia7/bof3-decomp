#ifndef OVERLAY_WORLD01_AREA038_13_H
#define OVERLAY_WORLD01_AREA038_13_H

/* The world01/area038/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

/* Retail calls it with int-width arguments in this image. */

/* Set three map cells in one column to the same byte. */
static inline void World01_SetMapCells(s32 column, s32 row0, s32 row1, s32 row2, s32 value) {
    Area_SetCellCode(column, row0, value);
    Area_SetCellCode(column, row1, value);
    Area_SetCellCode(column, row2, value);
}

#endif
