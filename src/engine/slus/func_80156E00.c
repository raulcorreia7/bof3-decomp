#include "engine/slus/slus.h"

/* probes the bundle cell grid. */

MATCH void func_80156E00(u8* unit, s32 x, s32 y) {
    s32 dx;
    s32 dy;
    s32 row;
    s32 col;
    s32 one;
    s32 next;
    s32 cell;

    dx  = x - g_AreaTileOriginX;
    dy  = y - g_AreaTileOriginY;
    row = dx + dy;
    if ((u32)row >= AREA_CELL_GRID_ROWS) {
        return;
    }
    next = row + 1;
    row  = g_AreaGridRowCursor + next;
    row  = (row >= AREA_CELL_GRID_ROWS) ? (row - AREA_CELL_GRID_ROWS) : row;
    col  = dx - dy;
    one  = 1;
    if ((u32)col >= AREA_CELL_GRID_ROWS) {
        return;
    }
    col  = g_AreaGridColCursor + (col / 2 + one);
    col  = (col >= AREA_CELL_GRID_COLS) ? (col - AREA_CELL_GRID_COLS) : col;
    cell = g_AreaCells[row][col].prim_id & AREA_CELL_PRIM_MASK;
    if (cell != 0) {
        Area_DrawCellQuad(unit[3] - 0x10, cell);
    }
}
