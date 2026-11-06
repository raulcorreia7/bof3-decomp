#include "engine/slus/slus.h"

/* walks the grid twice: each pass advances the column cursor from g_AreaGridColCursor (wrapping at the last column),
 * passes every cell of the row g_AreaGridRowCursor selects to func_801545B4 and func_801541C0, then steps
 * g_AreaGridRowCursor back (wrapping at the last row); the panel origin moves by (-1, -1). */
MATCH void func_80152E94(void) {
    s32       i;
    s32       rotCol;
    s32       col;
    s32       base;
    AreaCell* cell;

    for (i = 0; i < 2; i++) {
        rotCol = g_AreaGridColCursor;
        for (col = 0; col < 28; col++) {
            rotCol = (rotCol == AREA_CELL_GRID_COLS - 1) ? 0 : rotCol + 1;
            cell   = &g_AreaCells[g_AreaGridRowCursor][rotCol];
            Area_RequestCellRows(cell);
            if (i == 0) {
                base = -2;
            } else {
                base = -3;
            }
            Area_ProbeCell(base, col, cell);
        }
        g_AreaGridRowCursor = (g_AreaGridRowCursor != 0) ? g_AreaGridRowCursor - 1 : AREA_CELL_GRID_ROWS - 1;
    }
    g_AreaTileOriginX--;
    g_AreaTileOriginY--;
}
