#include "game_00.h"

MATCH u8 GFX_MarkPaletteCells(u8 mode, u8 value, u8 search) {
    u8 result;
    u8 row;
    u8 column;

    if (search != 0) {
        result = GFX_FindFreePaletteCell(mode);
    } else {
        result = GFX_FindPaletteCell(value);
        value  = 0xFF;
    }

    row    = ((u8*)&g_ScratchPad)[0];
    column = ((u8*)&g_ScratchPad)[1];
    switch (mode) {
        case PALETTE_TYPE_ROW:
            g_PaletteCells[row][column + 15] = value;
            g_PaletteCells[row][column + 14] = value;
            g_PaletteCells[row][column + 13] = value;
            g_PaletteCells[row][column + 12] = value;
            g_PaletteCells[row][column + 11] = value;
            g_PaletteCells[row][column + 10] = value;
            g_PaletteCells[row][column + 9]  = value;
            g_PaletteCells[row][column + 8]  = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_8:
            g_PaletteCells[row][column + 7] = value;
            g_PaletteCells[row][column + 6] = value;
            g_PaletteCells[row][column + 5] = value;
            g_PaletteCells[row][column + 4] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_4:
            g_PaletteCells[row][column + 3] = value;
            g_PaletteCells[row][column + 2] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_2:
            g_PaletteCells[row][column + 1] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELL:
            g_PaletteCells[row][column] = value;
            break;
        default:
            break;
    }
    return result;
}
