#include "game_00.h"

MATCH void func_801ACEBC(void) {
    Actor*                work;
    FieldSearchSpotStates table;

    work  = g_Task;
    table = D_80195ED4;
    table.states[work->unk_04]();
}
