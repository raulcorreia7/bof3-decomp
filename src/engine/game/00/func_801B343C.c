#include "game_00.h"

MATCH void func_801B343C(void) {
    if (func_801C4FE0() & BYTE_MASK) {
        g_Task->header.step = 2;
        g_Task->unk_03      = 0;
    }
}
