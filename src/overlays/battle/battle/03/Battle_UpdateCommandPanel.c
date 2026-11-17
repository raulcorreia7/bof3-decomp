#include "battle_03.h"

/* func_801D22AC */
MATCH void Battle_UpdateCommandPanel(void) {
    g_BattleCommandPanelSteps[g_Battle.phase.sub_step]();
}
