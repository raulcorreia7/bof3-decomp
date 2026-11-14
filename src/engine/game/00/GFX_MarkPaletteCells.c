#include "game_00.h"

MATCH u8 GFX_MarkPaletteCells(u8 mode, u8 value, u8 search) {
    u8 result;
    u8 row;
    u8 column;

    if (search != 0) {
        result = GFX_AllocPaletteCell(mode);
    } else {
        result = GFX_FindPaletteCell(value);
        value  = 0xFF;
    }

    row    = ((u8*)&D_1F800000)[0];
    column = ((u8*)&D_1F800000)[1];
    switch (mode) {
        case PALETTE_TYPE_ROW:
            D_80145D54[row][column + 0xF] = value;
            D_80145D54[row][column + 0xE] = value;
            D_80145D54[row][column + 0xD] = value;
            D_80145D54[row][column + 0xC] = value;
            D_80145D54[row][column + 0xB] = value;
            D_80145D54[row][column + 0xA] = value;
            D_80145D54[row][column + 0x9] = value;
            D_80145D54[row][column + 0x8] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_8:
            D_80145D54[row][column + 0x7] = value;
            D_80145D54[row][column + 0x6] = value;
            D_80145D54[row][column + 0x5] = value;
            D_80145D54[row][column + 0x4] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELLS_4:
            D_80145D54[row][column + 0x3] = value;
            D_80145D54[row][column + 0x2] = value;
            /* fallthrough */
        case PALETTE_KIND_CELLS_2:
            D_80145D54[row][column + 0x1] = value;
            /* fallthrough */
        case PALETTE_TYPE_CELL:
            D_80145D54[row][column] = value;
            break;
        default:
            break;
    }
    return result;
}
