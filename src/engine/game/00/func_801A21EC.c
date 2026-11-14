#include "game_00.h"

MATCH s32 func_801A21EC(s32 x, s32 y) {
    s32 value;
    /* FAKE: result pinned to v0. */
    FAKE_REG(s32, result, "v0");

    value  = Area_GetHeight(x, y, g_Task->direction_08 & 0x7);
    result = 0;
    if (SP_REF(u8, 0x0u) != 0) {
        result = (value << 16) > 0x400000;
    }
    return result;
}
