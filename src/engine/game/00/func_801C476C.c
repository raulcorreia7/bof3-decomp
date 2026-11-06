#include "game_00.h"

MATCH u8 func_801C476C(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells) {
    u8  cells[4];
    s16 x;
    s16 y;
    s32 i;

    x        = pos_x >> 16;
    y        = pos_y >> 16;
    cells[0] = Area_GetCellCode(x, y);
    cells[1] = Area_GetCellCode((s16)(x + 1), y);
    cells[2] = Area_GetCellCode(x, (s16)(y + 1));
    cells[3] = Area_GetCellCode((s16)(x + 1), (s16)(y + 1));
    for (i = 0; i < 4; i++) {
        if ((cells[i] & 0xF0) == 0x20) {
            cells[i] &= 0x21;
        }
    }
    if (mask_cells != 0) {
        for (i = 0; i < 4; i++) {
            cells[i] &= 0xF0;
        }
    }
    if (cells[0] == wanted_code) {
        /* @matching the shared fail and found exits keep the retail block order. */
        goto fail;
    }
    if (((pos_x & 0xFFFF) != 0) && (cells[1] == wanted_code)) {
        return 0;
    }
    if (((pos_y & 0xFFFF) != 0) && (cells[2] == wanted_code)) {
        return 0;
    }
    if (((pos_x & 0xFFFF) == 0) || ((pos_y & 0xFFFF) == 0) || (cells[3] != wanted_code)) {
        /* @matching shared success exit, placed after the fail exit. */
        goto found;
    }
fail:
    return 0;
found:
    return 1;
}
