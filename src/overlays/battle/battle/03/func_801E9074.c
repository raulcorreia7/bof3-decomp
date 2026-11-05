#include "battle_03.h"

MATCH void func_801E9074(void) {
    BattlePanelFuncs handlers;

    handlers = g_BattlePanelFuncs;
    handlers.handlers[((u8*)g_MenuCurrentPanel)[2]]();
}
