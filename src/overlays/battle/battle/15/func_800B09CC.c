#include "battle_15.h"

MATCH void func_800B09CC(void) {
    BattleHandlerTable3 handlers;

    handlers = D_80096A08;
    handlers.handlers[g_MenuCurrentPanel->state]();
}
