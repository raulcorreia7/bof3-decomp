#include "battle_15.h"

MATCH void func_8009A468(void) {
    SND_PlayCue(EMI_CUE_ID(1, 4));
    g_BattleSelectionLatch  = 0;
    D_801EB4D8[1]           = 5;
    BATTLE_ACTIVE_ROW->mode = 2;
    g_BattleCommandCount += 1u;
    D_801EB5B1[((D_801EC328 - 1) & 0xF) * 8] = 1u;
    func_8009B20C();
    g_BattleStep    = 1;
    g_BattleSubStep = 0;
    g_BattleUiStep  = 0;
    g_BattleUiState = 0;
}
