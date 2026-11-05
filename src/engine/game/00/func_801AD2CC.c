#include "game_00.h"

MATCH void func_801AD2CC(void) {
    Actor* work;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        work = g_Task;
        if (!(work->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
            func_8015BAC4(work->direction_08);
        }
        g_CurrentActor->interaction_flags = (g_CurrentActor->interaction_flags & ~ACTOR_FLAG_INTERACTION_PENDING);
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        g_Task->unk_04 = 0;
    }
}
