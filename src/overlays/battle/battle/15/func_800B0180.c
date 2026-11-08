#include "battle_15.h"

MATCH void func_800B0180(void) {
    Panel800969E4Modes handlers;

    handlers = D_800969E4;
    handlers.modes[g_MenuCurrentPanel->mode]();
}
