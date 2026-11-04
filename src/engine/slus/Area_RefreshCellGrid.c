#include "engine/slus/slus.h"

/* walks the 0x38 x 0x1C cell grid, advancing the row and column
 * cursors from g_AreaGridRowCursor/g_AreaGridColCursor with wraparound at 0x37/0x1B and passing
 * each rotated cell of g_AreaCells to func_801541C0, then calls func_80158B24.
 */
MATCH void Area_RefreshCellGrid(void) {
    s32 row;
    s32 col;
    s32 rotRow;
    s32 rotCol;

    rotRow = g_AreaGridRowCursor;
    for (row = 0; row < AREA_CELL_GRID_ROWS; row++) {
        rotRow = (rotRow == AREA_CELL_GRID_ROWS - 1) ? 0 : rotRow + 1;
        for (col = 0, rotCol = g_AreaGridColCursor; col < AREA_CELL_GRID_COLS; col++) {
            rotCol = (rotCol == AREA_CELL_GRID_COLS - 1) ? 0 : rotCol + 1;
            Area_ProbeCell(row, col, &g_AreaCells[rotRow][rotCol]);
        }
    }
    Area_IndexCells();
}
