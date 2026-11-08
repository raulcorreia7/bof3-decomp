#include "game_00.h"

MATCH void func_801ACEBC(void) {
    Actor*           work;
    ActorStateFuncs5 table;

    work  = g_Task;
    table = D_80195ED4;
    table.handlers[work->unk_04]();
}
