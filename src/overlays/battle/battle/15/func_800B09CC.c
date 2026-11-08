#include "battle_15.h"

MATCH void func_800B09CC(void) {
    Panel80096A08States handlers;

    handlers = D_80096A08;
    handlers.states[g_MenuCurrentPanel->state]();
}
