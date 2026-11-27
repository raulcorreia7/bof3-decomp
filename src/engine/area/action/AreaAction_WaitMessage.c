#include "engine/game/00/game_00.h"

/* func_801AD2CC */
MATCH void AreaAction_WaitMessage(void) {
    Actor* work;

    if (g_SysThreads[0].tail.game_entry.request != GAME_REQUEST_MESSAGE) {
        work = SELF(Actor);
        if (!(work->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
            Script_DispatchSelector(work->direction);
        }
        g_CurrentActor->interaction_flags = (g_CurrentActor->interaction_flags & ~ACTOR_INTERACTION_PENDING);
        g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
        SELF(Actor)->unk_04 = 0;
    }
}
