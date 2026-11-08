#include "battle_03.h"

MATCH void func_801E6C84(void) {
    BattleEffect3Steps handlers;

    handlers = D_801D0F44;
    if (g_Battle.phase.mode != 5) {
        g_ScriptBank = BATTLE_SCRIPT_BANK;
        handlers.steps[g_Task->header.mode]();
        g_ScriptBank = AREA_SCRIPT_BANK;
    }
}
