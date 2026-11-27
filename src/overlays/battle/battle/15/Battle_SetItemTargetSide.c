#include "battle_15.h"

/* func_800991B4 */
MATCH void Battle_SetItemTargetSide(void) {
    if (Item_GetFlags(g_UIPanelTasks[16].unk_0A, g_ItemCategoryIds[g_UIPanelTasks[16].unk_0A][g_UIPanelTasks[16].unk_0C]) & ITEM_SHOW_NAME) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
    } else {
        g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
    }
    g_Battle.ui_mode         = 1;
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1;
}
