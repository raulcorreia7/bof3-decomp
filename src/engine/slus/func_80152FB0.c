#include "engine/slus/slus.h"

/* walks two rotated rows of the cell grid: each pass advances the row cursor from g_AreaGridRowCursor (wrapping at the
 * last row) and the column cursor from g_AreaGridColCursor (wrapping at the last column) and passes each cell to
 * func_801545B4 and func_801541C0; the panel origin moves by (+1, +1). */
MATCH void func_80152FB0(void) {
    s32 row;
    s32 col;
    s32 rotRow;
    s32 rotCol;

    for (row = 0; row < 2; row++) {
        rotRow = (g_AreaGridRowCursor == AREA_CELL_GRID_ROWS - 1) ? 0 : g_AreaGridRowCursor + 1;
        rotCol = g_AreaGridColCursor;
        for (col = 0; col < 28; col++) {
            rotCol = (rotCol == AREA_CELL_GRID_COLS - 1) ? 0 : rotCol + 1;
            Area_RequestCellRows(&g_AreaCells[rotRow][rotCol]);
            Area_ProbeCell(row + AREA_CELL_GRID_ROWS, col, &g_AreaCells[rotRow][rotCol]);
        }
        g_AreaGridRowCursor = rotRow;
    }
    g_AreaTileOriginX++;
    g_AreaTileOriginY++;
}
