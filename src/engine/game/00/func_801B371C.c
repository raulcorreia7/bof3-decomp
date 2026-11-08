#include "game_00.h"

MATCH void func_801B371C(void) {
    Callback handler = D_801CD1B0[g_Task->header.step];

    handler();
    func_8014D978();
}
