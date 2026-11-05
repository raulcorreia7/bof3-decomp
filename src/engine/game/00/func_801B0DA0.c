#include "game_00.h"

MATCH void func_801B0DA0(void) {
    Actor* work;
    u8     count;

    g_GameState->mode_12B.u8_value = 1;
    work                           = g_Task;
    count                          = work->unk_09;
    if (count == 0) {
        func_801B146C();
    } else {
        work->unk_09 = count - 1;
        func_801B0DFC();
    }
}
