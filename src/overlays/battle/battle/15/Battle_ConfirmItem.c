#include "battle_15.h"

/* func_80098FD4 */
MATCH void Battle_ConfirmItem(void) {
    u8* cursor;
    u8* group;

    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
    cursor                          = &g_UIPanelTasks[16].unk_0C;
    group                           = cursor - 2;
    g_Battle.selection_latch        = 0u;
    g_BattleActorTurn->command.type = BATTLE_COMMAND_ITEM;
    g_BattleMessageSlot[1]          = 2u;

    g_Battle.command_count += 1u;
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].record_type = 1u;
    g_BattleActorTurn->choice                              = *cursor;
    if (g_ItemCategoryCounts[*group][*cursor] >= 2u) {
        g_ItemCategoryCounts[*group][*cursor] -= 1u;
    } else {
        /* FAKE: block boundary keeps the group read base-relative off the cursor la. */
        FAKE_ORDER_FENCE();
        g_ItemCategoryIds[*group][*cursor]    = 0;
        g_ItemCategoryCounts[*group][*cursor] = 0;
    }
    Battle_ClearMenuPanels();
    g_Battle.phase.step     = 1u;
    g_Battle.phase.sub_step = 0u;
    g_Battle.ui_step        = 0u;
    g_Battle.ui_mode        = 0u;
}
