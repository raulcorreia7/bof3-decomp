#include "battle_15.h"

MATCH void func_800B0CE4(void) {
    Panel80096A14States handlers;

    handlers = D_80096A14;
    handlers.states[g_MenuCurrentPanel->state]();
}
