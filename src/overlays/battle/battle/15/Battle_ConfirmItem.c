#include "battle_15.h"

/* func_80098FD4 */
MATCH void Battle_ConfirmItem(void) {
    u8* cursor;
    u8* group;

    SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 4));
    cursor                          = &g_MenuPanelTasks[16].unk_0C;
    group                           = cursor - 2;
    g_Battle.selection_latch        = 0u;
    g_BattleActorTurn->command.type = BATTLE_COMMAND_ITEM;
    g_BattleMessageSlot[1]          = 2u;

    g_Battle.command_count += 1u;
    D_801EB5B1[((D_801EC328 - 1) & 0xF) * 8] = 1u;
    g_BattleActorTurn->choice                = *cursor;
    if (D_801C8950[*group][*cursor] >= 2u) {
        D_801C8950[*group][*cursor] -= 1u;
    } else {
        /* FAKE: block boundary keeps the group read base-relative off the cursor la. */
        FAKE_ORDER_FENCE();
        D_801C893C[*group][*cursor] = 0;
        D_801C8950[*group][*cursor] = 0;
    }
    Battle_ClearMenuPanels();
    g_Battle.phase.step     = 1u;
    g_Battle.phase.sub_step = 0u;
    g_Battle.ui_step        = 0u;
    g_Battle.ui_mode        = 0u;
}
