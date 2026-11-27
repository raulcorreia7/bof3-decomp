#include "battle_15.h"

/* func_800982E4 */
MATCH void Battle_CancelExamine(void) {
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    g_UIPanelTasks[3].state = 1u;
    g_UIPanelTasks[2].state = 1u;
    Battle_ShowMessage((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    g_Battle.selection_latch = 0u;

    g_Battle.phase.step     = 2u;
    g_Battle.phase.sub_step = 0u;
    g_Battle.ui_step        = 0u;
}
