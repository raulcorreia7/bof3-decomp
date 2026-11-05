#include "battle_15.h"

MATCH void func_800B155C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_80096A40;
    handlers.handlers[g_MenuCurrentPanel->state]();
}
