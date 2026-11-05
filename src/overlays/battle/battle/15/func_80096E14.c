#include "battle_15.h"

MATCH void func_80096E14(void) {
    u8 counter;

    SND_PlayCue(EMI_CUE_ID(1, 4));
    g_BattleSelectionLatch  = 0;
    D_801EB4D8[1]           = 1;
    BATTLE_ACTIVE_ROW->mode = 2;
    counter                 = g_BattleCommandCount;
    g_BattleStep            = 1;
    g_BattleSubStep         = 0;
    g_BattleUiStep          = 0;
    g_BattleUiState         = 0;
    g_BattleCommandCount    = counter + 1;
}
