#include "battle_03.h"

MATCH void func_801E91FC(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801D0FAC;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
}
