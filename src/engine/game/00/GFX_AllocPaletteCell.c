#include "game_00.h"

MATCH u8 GFX_AllocPaletteCell(u8 mode) {
    u8  row;
    u8* map;
    u8  column;
    u8  end;
    s32 last;

    for (row = 0; row < PALETTE_MAP_ROWS; row++) {
        for (column = 0; column < PALETTE_MAP_COLUMNS; column++) {
            map = D_80145D54[row];
            if (map[column] == 0xFFu) {
                SP_REF(u8, 0x00u) = row;
                SP_REF(u8, 0x01u) = column;
                switch (mode) {
                    case PALETTE_KIND_CELL:
                        return (column + row * 16u - 0x40u);
                    case PALETTE_KIND_ROW:
                        if (column != 0u) {
                            break;
                        }
                        end  = column;
                        last = 0x0F;
                        while (end <= last) {
                            if (map[end] != 0xFFu) {
                                break;
                            }
                            end++;
                        }
                        if (end == 0x10u) {
                            return (row + (column >> 4) + 0x1Cu);
                        }
                        break;
                    case PALETTE_KIND_CELLS_2:
                        if ((column & 0x1u) != 0u) {
                            break;
                        }
                        end = column;
                        while (end <= column + 1) {
                            if (map[end] != 0xFFu) {
                                break;
                            }
                            end++;
                        }
                        if (end == column + 2) {
                            return (row * 8u + (column >> 1) - 0x20u);
                        }
                        break;
                    case PALETTE_KIND_CELLS_4:
                        if ((column & 0x3u) != 0u) {
                            break;
                        }
                        end = column;
                        while (end <= column + 3) {
                            if (map[end] != 0xFFu) {
                                break;
                            }
                            end++;
                        }
                        if (end == column + 4) {
                            return (row * 4u + (column >> 2) + 0x70u);
                        }
                        break;
                    case PALETTE_KIND_CELLS_8:
                        if ((column & 0x7u) != 0u) {
                            break;
                        }
                        end = column;
                        while (end <= column + 7) {
                            if (map[end] != 0xFFu) {
                                break;
                            }
                            end++;
                        }
                        if (end == column + 8) {
                            return (row * 2u + (column >> 3) + 0x38u);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return 0xFFu;
}
