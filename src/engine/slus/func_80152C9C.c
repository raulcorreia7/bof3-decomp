#include "engine/slus/slus.h"

/* walks one rotated column of the 56 x 28 cell grid (row cursor from g_AreaGridRowCursor wrapping at the last row,
 * column fixed at g_AreaGridColCursor), passing every cell to func_801545B4 and func_801541C0; the column cursor steps
 * back one (wrap to 0x1B) and the panel origin moves by (-1, +1). */
MATCH void func_80152C9C(void) {
    s32       row;
    s32       index;
    AreaCell* cell;

    row = g_AreaGridRowCursor;
    for (index = 0; index < AREA_CELL_GRID_ROWS; index++) {
        row  = (row == AREA_CELL_GRID_ROWS - 1) ? 0 : row + 1;
        cell = &g_AreaCells[row][g_AreaGridColCursor];
        Area_RequestCellRows(cell);
        Area_GetCell(index, -1, cell);
    }
    g_AreaGridColCursor = (g_AreaGridColCursor != 0) ? g_AreaGridColCursor - 1 : AREA_CELL_GRID_COLS - 1;
    g_AreaTileOriginX--;
    g_AreaTileOriginY++;
}
