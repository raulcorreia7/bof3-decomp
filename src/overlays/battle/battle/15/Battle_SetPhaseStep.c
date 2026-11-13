#include "battle_15.h"

/* func_80097CBC */
MATCH void Battle_SetPhaseStep(void) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    Battle_ShowMessage((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    g_Battle.phase.step      = 4u;
    g_Battle.selection_latch = 0u;

    g_Battle.phase.sub_step = 1u;
    g_Battle.ui_step        = 0u;
    g_Battle.ui_state       = 1u;
}
