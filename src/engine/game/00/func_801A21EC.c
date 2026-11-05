#include "game_00.h"

MATCH s32 func_801A21EC(s32 x, s32 y) {
    s32 value;
    /* FAKE: result pinned to v0. */
    MATCH_REG(s32, result, "v0");

    value  = ((s32 (*)(s32, s32, s32))func_80154ABC)(x, y, FIELD(u8, g_Task, 8u) & 7);
    result = 0;
    if (SP_REF(u8, 0x0u) != 0) {
        result = (value << 16) > 0x400000;
    }
    return result;
}
