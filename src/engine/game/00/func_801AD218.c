#include "game_00.h"

MATCH void func_801AD218(void) {
    Actor*          work;
    volatile Actor* area;

    work = g_Task;
    if (ACTOR_IN_USE(g_SpawnedActors[work->param.actor_slot])) {
        return;
    }
    if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        func_8015BAC4(work->direction_08);
    }
    area = GAME_WORK_AREA_PTR;
    area->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
    area         = g_Task;
    area->unk_04 = 0;
}
