#include "battle_03.h"

/* func_801D112C */
MATCH void Battle_DispatchMode(void) {
    BattlePhases handlers;

    handlers = g_BattlePhases;
    if (g_Battle.encounter != 0) {
        if (g_Battle.phase.mode != BATTLE_MODE_ENTRANCE) {
            g_Battle.boss_event_hook(BOSS_EVENT_TICK);
        }
    }
    handlers.handlers[g_Battle.phase.mode]();
}
