#include "game_00.h"

MATCH void func_801B6A04(void) {
    Actor* work;

    g_GameState->flags_12C.u8_value |= 4;
    D_801CD2D4[g_Task->unk_03]();
    work = g_Task;
    if ((work->option_flags & ACTOR_OPT_WAIT_STREAM) == 0) {
        if (work->header.flags & ACTOR_FLAG_STEP_MOVE) {
            func_8014D978();
        } else {
            func_8014DAEC();
        }
    }
}
