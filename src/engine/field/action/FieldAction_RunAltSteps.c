#include "engine/game/00/game_00.h"

/* func_801AD46C */
MATCH void FieldAction_RunAltSteps(void) {
    Actor*              work;
    FieldActionAltSteps table;

    work  = g_Task;
    table = g_FieldActionAltSteps;
    table.steps[work->unk_04]();
}
