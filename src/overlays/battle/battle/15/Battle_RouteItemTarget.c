#include "battle_15.h"

/* func_800989FC */
MATCH void Battle_RouteItemTarget(void) {
    u32 flags;

    flags = Item_GetFlags(g_UIPanelTasks[16].unk_0A, g_ItemCategoryIds[g_UIPanelTasks[16].unk_0A][g_UIPanelTasks[16].unk_0C]);
    if ((flags & ITEM_SHOW_ANIMATION) != 0u) {
        if ((flags & ITEM_STORY_ITEM) != 0u) {
            g_Battle.ui_step = 5u;
        } else {
            g_Battle.ui_step = 4u;
        }
        return;
    }
    if ((flags & ITEM_USABLE_MENU) != 0u) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_BOTH_SIDES;
    } else if ((flags & ITEM_STORY_ITEM) != 0u) {
        if ((flags & ITEM_SHOW_NAME) != 0u) {
            g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
        } else {
            g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
        }
    } else {
        g_BattleActorTurn->command.target = g_BattleMessageSlot[5];
    }
    g_Battle.ui_step = 4u;
    g_Battle.ui_mode = 3u;
}
