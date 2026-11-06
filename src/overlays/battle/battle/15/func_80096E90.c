#include "battle_15.h"

MATCH void func_80096E90(void) {
    SND_PlayCue(EMI_CUE_ID(1, 6));
    D_8014839F = 1u;
    D_8014837B = 1u;
    BattleStageMessageResource((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    g_BattleSelectionLatch = 0u;
    g_BattleStep           = 2u;
    g_BattleSubStep        = 0u;
    g_BattleUIStep         = 0u;
    g_BattleUIState        = 0u;
}
