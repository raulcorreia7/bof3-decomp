#include "game_00.h"

MATCH u8 GFX_AllocPaletteCell(u8 mode) {
    u8  row;
    u8* map;
    u8  column;
    u8  end;
    s32 last;

    for (row = 0; row < 4; row++) {
        for (column = 0; column < 16; column++) {
            map = D_80145D54[row];
            if (map[column] == 0xFFu) {
                SP_REF(u8, 0x00u) = row;
                SP_REF(u8, 0x01u) = column;
                switch (mode) {
                    case 0:
                        return (u8)(column + row * 16u - 0x40u);
                    case 1:
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
                            return (u8)(row + (column >> 4) + 0x1Cu);
                        }
                        break;
                    case 2:
                        if ((column & 1u) != 0u) {
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
                            return (u8)(row * 8u + (column >> 1) - 0x20u);
                        }
                        break;
                    case 3:
                        if ((column & 3u) != 0u) {
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
                            return (u8)(row * 4u + (column >> 2) + 0x70u);
                        }
                        break;
                    case 4:
                        if ((column & 7u) != 0u) {
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
                            return (u8)(row * 2u + (column >> 3) + 0x38u);
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
