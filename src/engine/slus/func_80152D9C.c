#include "engine/slus/slus.h"

/* rebuilds one rotated column of the 56 x 28 cell grid (column cursor from g_AreaGridColCursor wrapping at the last
 * column, row cursors from g_AreaGridRowCursor wrapping at the last row), passing every cell to func_801545B4 and
 * func_801541C0; the panel origin moves by (+1, -1). */
MATCH void func_80152D9C(void) {
    s32       row;
    s32       rotCol;
    s32       rotRow;
    AreaCell* cell;

    rotCol = 0;
    if (g_AreaGridColCursor != AREA_CELL_GRID_COLS - 1) {
        rotCol = g_AreaGridColCursor + 1;
    }
    rotRow = g_AreaGridRowCursor;
    for (row = 0; row < 56; row++) {
        rotRow = (rotRow == AREA_CELL_GRID_ROWS - 1) ? 0 : rotRow + 1;
        cell   = &g_AreaCells[rotRow][rotCol];
        Area_RequestCellRows(cell);
        Area_ProbeCell(row, 28, cell);
    }
    g_AreaGridColCursor = rotCol;
    g_AreaTileOriginX++;
    g_AreaTileOriginY--;
}
