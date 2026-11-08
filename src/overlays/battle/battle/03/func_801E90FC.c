#include "battle_03.h"

MATCH void func_801E90FC(void) {
    Panel801D0FA0States handlers;

    handlers = D_801D0FA0;
    handlers.states[BATTLE_PANEL_TASK->state]();
}
