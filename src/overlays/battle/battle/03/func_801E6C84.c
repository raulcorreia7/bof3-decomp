#include "battle_03.h"

MATCH void func_801E6C84(void) {
    Effect801D0F44Steps handlers;

    handlers = D_801D0F44;
    if (g_BattleMode != 5) {
        g_ScriptBank = BATTLE_SCRIPT_BANK;
        handlers.steps[g_Task->header.mode]();
        g_ScriptBank = AREA_SCRIPT_BANK;
    }
}
