#include "game_00.h"

MATCH void func_801AD218(void) {
    Actor*          work;
    volatile Actor* area;

    work = g_SpadWork;
    if (ACTOR_IN_USE(g_ActorSlots[work->unk_0B])) {
        return;
    }
    if ((work->option_flags & ACTOR_OPT_ROUTE_LOCKED) == 0) {
        func_8015BAC4(work->direction_08);
    }
    area = GAME_WORK_AREA_PTR;
    area->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
    g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
    area         = g_SpadWork;
    area->unk_04 = 0;
}
