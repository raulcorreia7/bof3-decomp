#include "game_00.h"

/* func_801AD6BC */
MATCH void FieldAction_RunFadeSteps(void) {
    Actor*               work;
    FieldActionFadeSteps table;

    work  = g_Task;
    table = g_FieldActionFadeSteps;
    table.steps[work->unk_04]();
}
