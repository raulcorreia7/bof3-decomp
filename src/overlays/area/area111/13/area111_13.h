#ifndef OVERLAY_WORLD02_AREA111_13_H
#define OVERLAY_WORLD02_AREA111_13_H

/* The world02/area111/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern SVECTOR D_1F800014[];
extern Actor   D_80147A58[];
extern u8      D_801F4890[];
extern u8      D_801F489C[];
/* The facing step bytes the cell walk advances by: x and y, one byte per facing. */
extern s8      D_80181B00[];
extern s8      D_80181B01[];
/* The cell grid's nibble table: four bytes per row, one nibble per cell. */
extern u8      D_801F5C18[];
/* One four-byte row of the packed cell map, which the restore step copies whole. */
#define AREA111_CELL_MAP_WORD(row) (*(u32*)&D_801F5C18[(row) * 4])
/* The grid's per-cell draw codes, seven rows of seven. */
extern u8  D_801F5BC8[7][7];
/* The seven-word template the packed cell map is restored from. */
extern u32 D_801F5BFC[];
/* g_SceneEventStep read unsigned: func_801F3EE8 switches on a byte load. */
extern u8  g_SceneEventStep_u8[];

void func_801F2DA0(void* arg0, s32 arg1, s32 arg2);

void func_801A4BC0(s32 arg0, s32 arg1, s32 arg2);
void func_801F4604(s32 cell_x, s32 cell_y, s32 tile_value);

#endif
