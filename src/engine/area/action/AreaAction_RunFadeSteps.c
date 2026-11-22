#include "engine/game/00/game_00.h"

/* func_801AD6BC */
MATCH void AreaAction_RunFadeSteps(void) {
    Actor*              work;
    AreaActionFadeSteps table;

    work  = TASK(Actor);
    table = g_AreaActionFadeSteps;
    table.steps[work->unk_04]();
}
