#include "battle_15.h"

MATCH void func_80096E90(void) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    D_8014839F = 1u;
    D_8014837B = 1u;
    Battle_ShowMessage((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    g_Battle.selection_latch = 0u;

    g_Battle.phase.step     = 2u;
    g_Battle.phase.sub_step = 0u;
    g_Battle.ui_step        = 0u;
    g_Battle.ui_state       = 0u;
}
