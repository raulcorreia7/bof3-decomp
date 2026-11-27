#include "battle_15.h"

/* func_8009A518 */
MATCH void Battle_CancelEquipItem(void) {
    u8 mode;

    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    Battle_ShowMessage((void*)BATTLE_ACTIVE_MESSAGE_SLOT_PTR);
    mode                      = 2;
    g_Battle.selection_latch  = 0;
    g_BattleChoicePhase       = mode;
    /* g_UIPanelTasks[16].pos.vx stays an address symbol here: a g_UIPanelTasks[16] view changes the code. */
    g_UIPanelTasks[16].pos.vx = -200;
    g_Battle.phase.step       = 4;
    g_Battle.phase.sub_step   = mode;
    g_Battle.ui_step          = 1;
    g_Battle.ui_mode          = 0;
}
