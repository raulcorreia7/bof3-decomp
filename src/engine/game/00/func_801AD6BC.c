#include "game_00.h"

MATCH void func_801AD6BC(void) {
    Actor*             work;
    ZennySpotFadeSteps table;

    work  = g_Task;
    table = D_80195F44;
    table.steps[work->unk_04]();
}
