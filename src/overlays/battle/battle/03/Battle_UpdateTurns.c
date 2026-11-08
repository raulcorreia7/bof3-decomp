#include "battle_03.h"

/* func_801D2AA8 */
MATCH void Battle_UpdateTurns(void) {
    D_801EAC10[g_Battle.phase.step]();
    if ((g_InputHeld & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.state &= ~BATTLE_STATE_COMMAND_ARMED;
    }
}
