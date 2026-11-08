#include "battle_03.h"

/* func_801D112C */
MATCH void Battle_DispatchMode(void) {
    BattlePhases handlers;

    handlers = g_BattlePhases;
    if (BATTLE_IS_SCRIPTED()) {
        if (g_Battle.phase.mode != BATTLE_MODE_ENTRANCE) {
            g_Battle.boss_event_hook(BOSS_EVENT_TICK);
        }
    }
    handlers.handlers[g_Battle.phase.mode]();
}
