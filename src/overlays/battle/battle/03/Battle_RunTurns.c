#include "battle_03.h"

/* func_801D2AA8 */
MATCH void Battle_RunTurns(void) {
    D_801EAC10[g_BattleStep]();
    if ((g_InputHeld & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_BattleState &= ~BATTLE_STATE_COMMAND_ARMED;
    }
}
