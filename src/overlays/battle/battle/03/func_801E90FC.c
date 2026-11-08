#include "battle_03.h"

MATCH void func_801E90FC(void) {
    BattlePanelStateFuncs3 handlers;

    handlers = D_801D0FA0;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
}
