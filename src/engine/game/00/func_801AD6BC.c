#include "game_00.h"

MATCH void func_801AD6BC(void) {
    Actor*              work;
    Actor80195F44States table;

    work  = g_Task;
    table = D_80195F44;
    table.states[work->unk_04]();
}
