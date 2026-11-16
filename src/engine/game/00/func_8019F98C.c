#include "game_00.h"

MATCH void func_8019F98C(void) {
    g_TaskModeHandlers[g_Task->header.mode]();
}
