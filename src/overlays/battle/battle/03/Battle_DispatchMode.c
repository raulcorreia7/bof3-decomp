#include "battle_03.h"

/* func_801D112C */
MATCH void Battle_DispatchMode(void) {
    BattlePhases handlers;

    handlers = g_BattlePhases;
    if (g_BattleEncounter != 0) {
        if (g_BattleMode != 0) {
            g_BossBattleEventHook(BOSS_EVENT_TICK);
        }
    }
    handlers.handlers[g_BattleMode]();
}
