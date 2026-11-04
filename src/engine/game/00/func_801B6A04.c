#include "game_00.h"

MATCH void func_801B6A04(void) {
    Actor* work;

    g_GameState->flags_12C.u8_value |= 4;
    D_801CD2D4[g_SpadWork->unk_03]();
    work = g_SpadWork;
    if ((work->option_flags & ACTOR_OPT_WAIT_STREAM) == 0) {
        if (work->flags_00 & ACTOR_FLAG_STEP_MOVE) {
            func_8014D978();
        } else {
            func_8014DAEC();
        }
    }
}
