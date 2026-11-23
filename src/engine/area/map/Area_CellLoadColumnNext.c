#include "engine/slus/slus.h"

/* rebuilds one rotated column of the 56 x 28 cell grid (column cursor from g_AreaMap.grid_column wrapping at the last
 * column, row cursors from g_AreaMap.grid_row wrapping at the last row), passing every cell to func_801545B4 and
 * func_801541C0; the panel origin moves by (+1, -1). */
/* func_80152D9C */
MATCH void Area_CellLoadColumnNext(void) {
    s32       row;
    s32       rotCol;
    s32       grid_row;
    AreaCell* cell;

    rotCol = 0;
    if (g_AreaMap.grid_column != AREA_CELL_GRID_COLS - 1) {
        rotCol = g_AreaMap.grid_column + 1;
    }
    grid_row = g_AreaMap.grid_row;
    for (row = 0; row < AREA_CELL_GRID_ROWS; row++) {
        grid_row = (grid_row == AREA_CELL_GRID_ROWS - 1) ? 0 : grid_row + 1;
        cell     = &g_AreaCells[grid_row][rotCol];
        Area_CellReleasePrims(cell);
        Area_CellGet(row, AREA_CELL_GRID_COLS, cell);
    }
    g_AreaMap.grid_column = rotCol;
    g_AreaMap.tile_origin_x++;
    g_AreaMap.tile_origin_y--;
}
