#include "battle_15.h"

MATCH void func_800B01F0(void) {
    BattlePanelStateFuncs3 handlers;

    handlers = D_800969F8;
    handlers.handlers[g_MenuCurrentPanel->state]();
}
