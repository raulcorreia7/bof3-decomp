#include "battle_03.h"

/* func_801E90FC */
MATCH void Battle_UpdatePartyPanel(void) {
    BattlePartyPanelSteps handlers;

    handlers = g_BattlePartyPanelSteps;
    handlers.steps[BATTLE_PANEL_TASK->state]();
}
