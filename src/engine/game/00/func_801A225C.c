#include "game_00.h"

MATCH s32 func_801A225C(s32 unused, s32 divisor, s32 flag_bits) {
    u8* work;

    if (flag_bits & 2) {
        work      = (u8*)g_SpadWork;
        work[9]   = (u8)(0x20 / (s32)(divisor & BYTE_MASK));
        work      = (u8*)g_SpadWork;
        work[0xA] = (u8)(work[9] >> 1);
    }
    return 1;
}
