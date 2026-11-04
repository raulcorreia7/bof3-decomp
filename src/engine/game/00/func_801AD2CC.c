#include "game_00.h"

MATCH void func_801AD2CC(void) {
    Actor* work;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        work = g_SpadWork;
        if (!(work->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
            func_8015BAC4(work->direction_08);
        }
        g_CurrentActor->flags_74 = (u8)(g_CurrentActor->flags_74 & ~ACTOR_FLAG_INTERACTION_PENDING);
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        g_SpadWork->unk_04 = 0;
    }
}
