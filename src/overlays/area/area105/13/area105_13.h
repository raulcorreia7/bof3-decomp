#ifndef OVERLAY_WORLD02_AREA105_13_H
#define OVERLAY_WORLD02_AREA105_13_H

/* The world02/area105/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

extern u8 D_801F3320[];

/* A cell row func_801F2D9C draws: its first cell and its size, in cells. */
typedef struct Area105CellRow {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
} Area105CellRow;

extern Area105CellRow g_Area105CellRows[3]; /* D_801F3320 + 0x10 */

void func_801F2D9C(s32);

#endif
