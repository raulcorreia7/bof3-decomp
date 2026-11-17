#include "game_00.h"

MATCH void func_801AD46C(void) {
    Actor*            work;
    ZennySpotAltSteps table;

    work  = g_Task;
    table = D_80195F10;
    table.steps[work->unk_04]();
}
