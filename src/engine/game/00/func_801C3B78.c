#include "game_00.h"

MATCH s32 func_801C3B78(s32 pos_x, s32 pos_y, s32 wanted_code, s32 mask_cells) {
    u8  cells[4];
    u8* cell;
    u8  single;
    s16 x_hi;
    s16 y_hi;
    s16 x_next;
    s16 y_next;
    s16 x_prev;
    s16 y_prev;
    s32 x_raw;
    s32 y_raw;
    s32 wanted;
    s32 mask;

    x_hi     = pos_x >> 0x10;
    y_hi     = pos_y >> 0x10;
    wanted   = wanted_code;
    mask     = mask_cells;
    cells[0] = AREA_CELL_CODE_S16(x_hi, y_hi);
    x_next   = x_hi + 1;
    y_next   = y_hi + 1;
    cells[1] = AREA_CELL_CODE_S16(x_next, y_hi);
    cells[2] = AREA_CELL_CODE_S16(x_hi, y_next);
    cells[3] = AREA_CELL_CODE_S16(x_next, y_next);
    cell     = cells;
    if (mask & BYTE_MASK) {
        do {
            *cell &= 0xF0;
            cell += 1;
        } while ((s32)cell < (s32)(cells + 4));
    }
    if (cells[0] != (wanted & BYTE_MASK)) {
        return 0;
    }
    if (cells[1] != cells[0]) {
        return 0;
    }
    if (cells[2] != cells[1]) {
        return 0;
    }
    if (cells[3] != cells[2]) {
        return 0;
    }
    if (!(pos_x & HALF_MASK)) {
        x_prev   = (pos_x >> 0x10) - 1;
        y_raw    = pos_y >> 0x10;
        cells[0] = AREA_CELL_CODE_S16(x_prev, y_raw);
        cells[1] = AREA_CELL_CODE_S16(x_prev, y_raw + 1);
        cell     = cells;
        if (mask & BYTE_MASK) {
            do {
                *cell &= 0xF0;
                cell += 1;
            } while ((s32)cell < (s32)(cells + 2));
        }
        if (cells[0] != (wanted & BYTE_MASK)) {
            return 0;
        }
        if (cells[1] != cells[0]) {
            return 0;
        }
    }
    if ((pos_y & HALF_MASK) == 0) {
        x_raw    = pos_x >> 0x10;
        y_prev   = (pos_y >> 0x10) - 1;
        cells[0] = AREA_CELL_CODE_S16(x_raw, y_prev);
        cells[1] = AREA_CELL_CODE_S16(x_raw + 1, y_prev);
        cell     = cells;
        if (mask & BYTE_MASK) {
            do {
                *cell &= 0xF0;
                cell += 1;
            } while ((s32)cell < (s32)(cells + 2));
        }
        if (cells[0] != (wanted & BYTE_MASK)) {
            return 0;
        }
        if (cells[1] != cells[0]) {
            return 0;
        }
    }
    if ((pos_x & HALF_MASK) != 0) {
        return 1;
    }
    if (pos_y & HALF_MASK) {
        return 1;
    }
    single   = AREA_CELL_CODE_S16((pos_x >> 0x10) - 1, (pos_y >> 0x10) - 1);
    cells[0] = single;
    if (mask & BYTE_MASK) {
        cells[0] = single & 0xF0;
    }
    if (cells[0] == (wanted & BYTE_MASK)) {
        return 1;
    }
    /* Distinct local keeps the compare above a branch; `return 0` is if-converted to xor/sltiu. */
    x_raw = 0;
    return x_raw;
}
