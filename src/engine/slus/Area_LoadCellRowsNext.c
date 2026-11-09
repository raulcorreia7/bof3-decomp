#include "engine/slus/slus.h"

/* walks two rotated rows of the cell grid. */
/* func_80152FB0 */
MATCH void Area_LoadCellRowsNext(void) {
    s32 row;
    s32 col;
    s32 rotRow;
    s32 rotCol;

    for (row = 0; row < 2; row++) {
        rotRow = (g_AreaGridRowCursor == AREA_CELL_GRID_ROWS - 1) ? 0 : g_AreaGridRowCursor + 1;
        rotCol = g_AreaGridColCursor;
        for (col = 0; col < AREA_CELL_GRID_COLS; col++) {
            rotCol = (rotCol == AREA_CELL_GRID_COLS - 1) ? 0 : rotCol + 1;
            Area_RequestCellRows(&g_AreaCells[rotRow][rotCol]);
            Area_GetCell(row + AREA_CELL_GRID_ROWS, col, &g_AreaCells[rotRow][rotCol]);
        }
        g_AreaGridRowCursor = rotRow;
    }
    g_AreaTileOriginX++;
    g_AreaTileOriginY++;
}
