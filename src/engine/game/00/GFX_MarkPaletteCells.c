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
            g_PaletteCells[row][column + 0xF] = value;
            g_PaletteCells[row][column + 0xE] = value;
            g_PaletteCells[row][column + 0xD] = value;
            g_PaletteCells[row][column + 0xC] = value;
            g_PaletteCells[row][column + 0xB] = value;
            g_PaletteCells[row][column + 0xA] = value;
            g_PaletteCells[row][column + 0x9] = value;
            g_PaletteCells[row][column + 0x8] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_8:
            g_PaletteCells[row][column + 0x7] = value;
            g_PaletteCells[row][column + 0x6] = value;
            g_PaletteCells[row][column + 0x5] = value;
            g_PaletteCells[row][column + 0x4] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_4:
            g_PaletteCells[row][column + 0x3] = value;
            g_PaletteCells[row][column + 0x2] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_2:
            g_PaletteCells[row][column + 0x1] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELL:
            g_PaletteCells[row][column] = value;
            break;
        default:
            break;
    }
    return result;
}
