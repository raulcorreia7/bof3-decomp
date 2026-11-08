#include "game_00.h"

MATCH s32 func_801BB760(s32 x, s32 y) {
    s32 value;
    /* FAKE: result pinned to v0; allocator picks a0 without it. */
    FAKE_REG(s32, result, "v0");

    value  = ((s32 (*)(s32, s32, u8))Area_ReadStepHeight)(x, y, g_Task->direction_08);
    result = 0;
    if (SP_REF(u8, 0x0u) != 0) {
        result = (value << 0x10) > 0x400000;
    }
    return result;
}
