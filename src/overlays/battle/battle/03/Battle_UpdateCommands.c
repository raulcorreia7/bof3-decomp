#include "battle_03.h"

/* func_801D1C54 */
MATCH void Battle_UpdateCommands(void) {
    g_BattleCommandSteps[g_Battle.phase.step]();
}
