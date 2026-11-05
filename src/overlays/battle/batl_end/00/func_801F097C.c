#include "batl_end_00.h"

MATCH void func_801F097C(void) {
    Callback table[2] = {func_801F09D4, func_801F09F4};

    table[BATTLE_PANEL_TASK->state]();
}
