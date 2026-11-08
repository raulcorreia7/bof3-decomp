#include "battle_15.h"

MATCH void func_800B01F0(void) {
    Panel800969F8States handlers;

    handlers = D_800969F8;
    handlers.states[g_MenuCurrentPanel->state]();
}
