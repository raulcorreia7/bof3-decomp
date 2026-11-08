#include "battle_15.h"

MATCH void func_800B155C(void) {
    Panel80096A40States handlers;

    handlers = D_80096A40;
    handlers.states[g_MenuCurrentPanel->state]();
}
