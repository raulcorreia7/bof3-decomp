#include "battle_03.h"

MATCH void func_801E943C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801D0FB8;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
}
