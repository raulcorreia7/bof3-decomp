#include "battle_15.h"

MATCH void func_8009A518(void) {
    u8 mode;

    SND_PlayCue(EMI_CUE_ID(1, 6));
    BattleStageMessageResource((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    mode                     = 2;
    g_Battle.selection_latch = 0;
    g_BattleChoicePhase      = mode;
    /* D_80148574 stays an address symbol here: a g_MenuPanelTasks[16] view changes the code. */
    D_80148574               = -200;
    g_Battle.phase.step      = 4;
    g_Battle.phase.sub_step  = mode;
    g_Battle.ui_step         = 1;
    g_Battle.ui_state        = 0;
}
