#include "engine/game/00/game_00.h"

/* func_801ACEBC */
MATCH void FieldAction_RunSteps(void) {
    Actor*           work;
    FieldActionSteps table;

    work  = g_Task;
    table = g_FieldActionSteps;
    table.steps[work->unk_04]();
}
