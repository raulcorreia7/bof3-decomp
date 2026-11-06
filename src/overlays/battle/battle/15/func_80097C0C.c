#include "battle_15.h"

MATCH void func_80097C0C(void) {
    SND_PlayCue(EMI_CUE_ID(1, 4));
    g_BattleSelectionLatch   = 0;
    D_801EB4D8->command.type = BATTLE_COMMAND_ABILITY;
    g_BattleMessageSlot[1]   = 2;
    g_BattleCommandCount += 1u;
    D_801EB5B1[((D_801EC328 - 1) & 0xF) * 8] = 1u;
    func_8009B20C();
    g_BattleStep    = 1;
    g_BattleSubStep = 0;
    g_BattleUIStep  = 0;
    g_BattleUIState = 0;
}
