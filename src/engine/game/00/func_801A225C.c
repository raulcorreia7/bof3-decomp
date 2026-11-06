#include "game_00.h"

MATCH s32 func_801A225C(s32 unused, s32 divisor, s32 flag_bits) {
    u8* work;

    if (flag_bits & 2) {
        work      = (u8*)g_Task;
        work[9]   = (0x20 / (divisor & 0xFF));
        work      = (u8*)g_Task;
        work[0xA] = (work[9] >> 1);
    }
    return 1;
}
