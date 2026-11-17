#include "battle_03.h"

/* func_801E91FC */
MATCH void Battle_UpdateMenuRowsPanel(void) {
    BattleMenuRowsPanelSteps handlers;

    handlers = g_BattleMenuRowsPanelSteps;
    handlers.steps[BATTLE_PANEL_TASK->state]();
}
