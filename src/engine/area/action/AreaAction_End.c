#include "engine/game/00/game_00.h"

/* func_801AD218 */
MATCH void AreaAction_End(void) {
    Actor*          work;
    volatile Actor* area;

    work = SELF(Actor);
    if (ACTOR_IN_USE(g_SpawnedActors[work->param.actor_slot])) {
        return;
    }
    if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        Script_DispatchSelector(work->direction);
    }
    area = GAME_WORK_AREA_PTR;
    area->interaction_flags &= ~ACTOR_INTERACTION_PENDING;
    g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
    area         = SELF(Actor);
    area->unk_04 = 0;
}
