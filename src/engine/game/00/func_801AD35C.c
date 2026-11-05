#include "game_00.h"

MATCH void func_801AD35C(void) {
    Actor*   work        = g_Task;
    Callback handlers[2] = {func_801AD3B4, func_801AD218};

    handlers[work->unk_04]();
}
