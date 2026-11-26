#include "engine/game/00/game_00.h"

/* func_801ACEBC */
MATCH void AreaAction_RunSteps(void) {
    Actor*          work;
    AreaActionSteps table;

    work  = SELF(Actor);
    table = g_AreaActionSteps;
    table.steps[work->unk_04]();
}
