#include "game_00.h"

MATCH void func_801AD46C(void) {
    Actor*           work;
    ActorStateFuncs5 table;

    work  = g_Task;
    table = D_80195F10;
    table.handlers[work->unk_04]();
}
