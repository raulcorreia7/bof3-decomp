#include "batl_end_00.h"

MATCH void func_801F0768(void) {
    Callback table[2] = {func_801F07C0, func_801F07E0};

    table[BATTLE_PANEL_TASK->state]();
}
