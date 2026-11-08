#include "battle_15.h"

MATCH void func_800B0CE4(void) {
    BattlePanelStateFuncs5 handlers;

    handlers = D_80096A14;
    handlers.handlers[g_MenuCurrentPanel->state]();
}
