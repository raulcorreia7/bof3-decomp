#include "game_00.h"

MATCH u8 func_801C48FC(s32 pos_x, s32 pos_y, u8 wanted_code, u8 mask_cells) {
    u8  cells[4];
    s32 i;

    cells[0] = Area_GetCellCode(pos_x >> 16, pos_y >> 16);
    cells[1] = Area_GetCellCode((s16)((pos_x >> 16) + 1), pos_y >> 16);
    cells[2] = Area_GetCellCode(pos_x >> 16, (s16)((pos_y >> 16) + 1));
    cells[3] = Area_GetCellCode((s16)((pos_x >> 16) + 1), (s16)((pos_y >> 16) + 1));
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
    if ((cells[0] == wanted_code) || (cells[1] == wanted_code) || (cells[2] == wanted_code) || (cells[3] == wanted_code)) {
        /* @matching single failure exit keeps the four compares ahead of the tail. */
        goto fail;
    }
    if ((pos_x & HALF_MASK) == 0) {
        cells[0] = Area_GetCellCode((s16)((pos_x >> 16) - 1), pos_y >> 16);
        cells[1] = Area_GetCellCode((s16)((pos_x >> 16) - 1), (s16)((pos_y >> 16) + 1));
        if ((cells[0] & 0xF0) == 0x20) {
            cells[0] &= 0x21;
        }
        if ((cells[1] & 0xF0) == 0x20) {
            cells[1] &= 0x21;
        }
        if (mask_cells != 0) {
            for (i = 0; i < 4; i++) {
                cells[i] &= 0xF0;
            }
        }
        if ((cells[0] == wanted_code) || (cells[1] == wanted_code)) {
            /* @matching single failure exit. */
            goto fail;
        }
    }
    if ((pos_y & HALF_MASK) == 0) {
        cells[0] = Area_GetCellCode(pos_x >> 16, (s16)((pos_y >> 16) - 1));
        cells[1] = Area_GetCellCode((s16)((pos_x >> 16) + 1), (s16)((pos_y >> 16) - 1));
        if ((cells[0] & 0xF0) == 0x20) {
            cells[0] &= 0x21;
        }
        if ((cells[1] & 0xF0) == 0x20) {
            cells[1] &= 0x21;
        }
        if (mask_cells != 0) {
            for (i = 0; i < 4; i++) {
                cells[i] &= 0xF0;
            }
        }
        if ((cells[0] == wanted_code) || (cells[1] == wanted_code)) {
            /* @matching single failure exit. */
            goto fail;
        }
    }
    if (((pos_x & HALF_MASK) != 0) || ((pos_y & HALF_MASK) != 0)) {
        return 1;
    }
    cells[0] = Area_GetCellCode((s16)((pos_x >> 16) - 1), (s16)((pos_y >> 16) - 1));
    if (mask_cells != 0) {
        cells[0] &= 0xF0;
    }
    if (cells[0] != wanted_code) {
        /* @matching tail: the corner value selects the shared success exit. */
        goto found;
    }
fail:
    return 0;
found:
    return 1;
}
