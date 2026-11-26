#include "engine/game/00/game_00.h"

/* func_8019D20C */
/* Returns whether one map cell code stops the block. */
MATCH s32 Actor_BlockIsCellSolid(s16 map_x, s16 map_y) {
    s32 value                   = Area_CellGetCode(map_x, map_y);
    s32 low                     = value & BYTE_MASK;
    /* FAKE: result pinned to v0; retail keeps the return value live. */
    FAKE_REG(s32, result, "v0") = 0;

    if (low != 0 && low != 0xC0 && (value & 0xF0) != 0x80 && (value & 0xF0) != 0xA0) {
        result = low != 0x20;
    }
    return result;
}
