#include "game_00.h"

MATCH void func_801B343C(void) {
    if (func_801C4FE0() & BYTE_MASK) {
        TASK(Actor)->header.step = 2;
        TASK(Actor)->unk_03      = 0;
    }
}
