#include "battle_15.h"

MATCH void func_80099114(void) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    Battle_ShowMessage((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    g_Battle.phase.step      = 4u;
    g_Battle.phase.sub_step  = 2u;
    g_Battle.selection_latch = 0u;

    g_Battle.ui_step  = 0u;
    g_Battle.ui_state = 1u;
}
