#include "battle_03.h"

/* func_801EA7DC */
MATCH void Battle_UpdateMessagePanel(void) {
    BattleMessagePanelSteps table = g_BattleMessagePanelSteps;

    table.steps[g_UIPanelCurrent->state]();
}
