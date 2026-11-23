#include "game_00.h"

MATCH s32 func_801A225C(s32 unused, s32 divisor, s32 flag_bits) {
    Actor* work;

    if (flag_bits & 0x2) {
        work         = TASK(Actor);
        work->timer  = (0x20 / (divisor & BYTE_MASK));
        work         = TASK(Actor);
        work->unk_0A = (work->timer >> 1);
    }
    return 1;
}
