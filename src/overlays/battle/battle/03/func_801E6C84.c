#include "battle_03.h"

MATCH void func_801E6C84(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801D0F44;
    if (g_BattleMode != 5) {
        g_ScriptBank = BATTLE_SCRIPT_BANK;
        handlers.handlers[g_Task->header.mode]();
        g_ScriptBank = AREA_SCRIPT_BANK;
    }
}
