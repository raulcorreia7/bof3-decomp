#include "battle_15.h"

MATCH void func_800B0180(void) {
    BattleHandlerTable5 handlers;

    handlers = D_800969E4;
    handlers.handlers[g_MenuCurrentPanel->mode]();
}
