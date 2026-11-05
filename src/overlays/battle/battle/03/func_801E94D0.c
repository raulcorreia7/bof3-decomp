#include "battle_03.h"

MATCH void func_801E94D0(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801D0FC4;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
}
