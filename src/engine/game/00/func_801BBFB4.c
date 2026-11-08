#include "game_00.h"

MATCH void func_801BBFB4(void) {
    Callback handler = D_801CD440[g_Task->header.step];
    handler();
    func_8014D978();
}
