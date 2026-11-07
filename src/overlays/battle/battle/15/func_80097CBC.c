#include "battle_15.h"

MATCH void func_80097CBC(void) {
    SND_PlayCue(EMI_CUE_ID(1, 6));
    BattleStageMessageResource((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    g_BattleStep           = 4u;
    g_BattleSelectionLatch = 0u;

    g_BattleSubStep = 1u;
    g_BattleUIStep  = 0u;
    g_BattleUIState = 1u;
}
