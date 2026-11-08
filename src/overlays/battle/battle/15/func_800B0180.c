#include "battle_15.h"

MATCH void func_800B0180(void) {
    BattleMenuPanelModes handlers;

    handlers = D_800969E4;
    handlers.modes[g_MenuCurrentPanel->mode]();
}
