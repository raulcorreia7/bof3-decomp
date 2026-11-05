#include "battle_15.h"

MATCH void func_800B138C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_80096A34;
    handlers.handlers[g_MenuCurrentPanel->state]();
}
