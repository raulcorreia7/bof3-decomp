#include "game_00.h"

MATCH s32 func_8019D20C(s16 map_x, s16 map_y) {
    s32 value                    = Area_GetCellCode(map_x, map_y);
    s32 low                      = value & BYTE_MASK;
    /* FAKE: result pinned to v0; retail keeps the return value live. */
    MATCH_REG(s32, result, "v0") = 0;

    if (low != 0 && low != 0xC0 && (value & 0xF0) != 0x80 && (value & 0xF0) != 0xA0) {
        result = low != 0x20;
    }
    return result;
}
