#include "game_00.h"

MATCH void func_8019E918(void) {
    Callback handler = D_801C81B8[g_Task->header.step];
    handler();
}
