#include "engine/game/00/game_00.h"

/* func_801AD46C */
MATCH void AreaAction_RunAltSteps(void) {
    Actor*             work;
    AreaActionAltSteps table;

    work  = SELF(Actor);
    table = g_AreaActionAltSteps;
    table.steps[work->unk_04]();
}
