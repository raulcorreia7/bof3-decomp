#include "batl_end_00.h"

MATCH void func_801EFE10(void) {
    Callback handlers[2];

    handlers[0] = func_801EFE5C;
    handlers[BATTLE_PANEL_TASK->state]();
}
