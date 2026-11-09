#include "battle_03.h"

MATCH void func_801E6C84(void) {
    BattleEffect3Steps handlers;

    handlers = D_801D0F44;
    if (g_Battle.phase.mode != BATTLE_MODE_RESULT) {
        g_ScriptTable = BATTLE_SCRIPT_TABLE;
        handlers.steps[g_Task->header.mode]();
        g_ScriptTable = AREA_SCRIPT_TABLE;
    }
}
