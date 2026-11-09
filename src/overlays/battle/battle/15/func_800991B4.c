#include "battle_15.h"

MATCH void func_800991B4(void) {
    if (Item_GetFlags(g_MenuPanelTasks[16].unk_0A, D_801C893C[g_MenuPanelTasks[16].unk_0A][g_MenuPanelTasks[16].unk_0C]) & 0x20u) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
    } else {
        g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
    }
    g_Battle.ui_state        = 1;
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1;
}
