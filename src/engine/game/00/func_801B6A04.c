#include "game_00.h"

MATCH void func_801B6A04(void) {
    Actor* work;

    g_Game.current->status.field.flags.unsigned_value |= 4;
    D_801CD2D4[g_Task->unk_03]();
    work = g_Task;
    if ((work->option_flags & ACTOR_OPT_WAIT_STREAM) == 0) {
        if (work->header.flags & ACTOR_FLAG_STEP_MOVE) {
            Script_AnimStepLoop();
        } else {
            Script_AnimStepOnce();
        }
    }
}
