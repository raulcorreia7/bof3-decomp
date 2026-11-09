#include "engine/slus/slus.h"

/* probes the bundle cell grid. */

MATCH s32 Area_GetCellId(s32 x, s32 y) {
    s32 dx;
    s32 dy;
    s32 row;
    s32 col;
    s32 one; /* FAKE: the addend must live in its own local; inlining the 1 measures 97.87. */
    s32 next;

    dx  = x - g_AreaTileOriginX;
    dy  = y - g_AreaTileOriginY;
    row = dx + dy;
    if ((u32)row >= AREA_CELL_GRID_ROWS) {
        return 0;
    }
    next = row + 1;
    row  = g_AreaGridRowCursor + next;
    row  = (row >= AREA_CELL_GRID_ROWS) ? (row - AREA_CELL_GRID_ROWS) : row;
    col  = dx - dy;
    one  = 1;
    if ((u32)col >= AREA_CELL_GRID_ROWS) {
        return 0;
    }
    col = g_AreaGridColCursor + (col / 2 + one);
    col = (col >= AREA_CELL_GRID_COLS) ? (col - AREA_CELL_GRID_COLS) : col;
    return g_AreaCells[row][col].prim_id & AREA_CELL_PRIM_MASK;
}
