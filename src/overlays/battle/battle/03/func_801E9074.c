#include "battle_03.h"

MATCH void func_801E9074(void) {
    BattlePanelModes handlers;

    handlers = g_BattlePanelFuncs;
    handlers.modes[g_MenuCurrentPanel->mode]();
}
