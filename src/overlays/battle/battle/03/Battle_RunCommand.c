#include "battle_03.h"

/* func_801D24D4 */
MATCH void Battle_RunCommand(void) {
    func_801DD800();
    g_BattleRunCommandSteps[g_Battle.phase.sub_step]();
}
