#include "battle_15.h"

/* func_80098B44 */
MATCH void Battle_StartItemTarget(void) {
    u32 flags;

    flags = Item_GetFlags(g_UIPanelTasks[16].unk_0A, g_ItemCategoryIds[g_UIPanelTasks[16].unk_0A][g_UIPanelTasks[16].unk_0C]);
    if ((flags & ITEM_SHOW_NAME) != 0u) {
        g_BattleActorTurn->command.target = Battle_TargetNext(3);
        g_Battle.ui_mode                  = 1u;
    } else if (func_8009AF7C() != 0u) {
        g_BattleActorTurn->command.target = 0u;
        g_Battle.ui_mode                  = 2u;
    } else {
        g_BattleActorTurn->command.target = Battle_TargetNext(0);
        g_Battle.ui_mode                  = 2u;
    }
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1u;
}
