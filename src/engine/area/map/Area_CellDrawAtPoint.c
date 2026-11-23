#include "engine/slus/slus.h"

/* probes the bundle cell grid: the (x, y) delta becomes a row/column pair (both outside 0x38 reject), rotated by the
 * cursor offsets g_AreaGridRowCursor/g_AreaGridColCursor; when the low 12 bits of the prim_slot of the rotated
 * g_AreaCells entry are set they go to func_80156ED4 with the slot byte minus 0x10. */

MATCH void Area_CellDrawAtPoint(u8* unit, s32 x, s32 y) {
    s32 dx;
    s32 dy;
    s32 row;
    s32 col;
    s32 one;
    s32 next;
    s32 cell;

    dx  = x - g_AreaMap.tile_origin_x;
    dy  = y - g_AreaMap.tile_origin_y;
    row = dx + dy;
    if ((u32)row >= AREA_CELL_GRID_ROWS) {
        return;
    }
    next = row + 1;
    row  = g_AreaMap.grid_row + next;
    row  = (row >= AREA_CELL_GRID_ROWS) ? (row - AREA_CELL_GRID_ROWS) : row;
    col  = dx - dy;
    one  = 1;
    if ((u32)col >= AREA_CELL_GRID_ROWS) {
        return;
    }
    col  = g_AreaMap.grid_column + (col / 2 + one);
    col  = (col >= AREA_CELL_GRID_COLS) ? (col - AREA_CELL_GRID_COLS) : col;
    cell = g_AreaCells[row][col].prim_slot & AREA_CELL_PRIM_MASK;
    if (cell != 0) {
        Area_CellDrawQuad(unit[3] - 0x10, cell);
    }
}
