#include "game_00.h"

MATCH void func_801ACEBC(void) {
    Actor*               work;
    FieldSearchSpotSteps table;

    work  = g_Task;
    table = D_80195ED4;
    table.steps[work->unk_04]();
}
