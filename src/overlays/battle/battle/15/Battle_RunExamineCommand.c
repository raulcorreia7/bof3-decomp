#include "battle_15.h"

/* func_800980A8 */
MATCH void Battle_RunExamineCommand(void) {
    g_BattleExamineSteps[g_Battle.ui_step]();
}
