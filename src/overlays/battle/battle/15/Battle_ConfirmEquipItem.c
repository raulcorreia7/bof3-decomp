#include "battle_15.h"

/* func_8009A468 */
MATCH void Battle_ConfirmEquipItem(void) {
    SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 4));
    g_Battle.selection_latch        = 0;
    g_BattleActorTurn->command.type = BATTLE_COMMAND_ITEM;

    BATTLE_ACTIVE_ROW->header.mode = 2;
    g_Battle.command_count += 1u;
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].record_type = 1u;
    Battle_ClearMenuPanels();
    g_Battle.phase.step     = 1;
    g_Battle.phase.sub_step = 0;
    g_Battle.ui_step        = 0;
    g_Battle.ui_mode        = 0;
}
