#include "battle_15.h"

MATCH void func_800B138C(void) {
    Panel80096A34States handlers;

    handlers = D_80096A34;
    handlers.states[g_MenuCurrentPanel->state]();
}
