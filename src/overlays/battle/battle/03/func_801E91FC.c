#include "battle_03.h"

MATCH void func_801E91FC(void) {
    BattlePanelStateFuncs3 handlers;

    handlers = D_801D0FAC;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
}
