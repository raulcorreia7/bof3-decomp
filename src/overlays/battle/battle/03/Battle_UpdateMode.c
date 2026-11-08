#include "battle_03.h"

/* func_801D112C */
MATCH void Battle_UpdateMode(void) {
    BattlePhases handlers;

    handlers = g_BattlePhases;
    if (g_Battle.encounter != 0) {
        if (g_Battle.phase.mode != 0) {
            g_Battle.boss_event_hook(BOSS_EVENT_TICK);
        }
    }
    handlers.handlers[g_Battle.phase.mode]();
}
