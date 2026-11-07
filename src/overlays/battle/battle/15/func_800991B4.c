#include "battle_15.h"

MATCH void func_800991B4(void) {
    if (Item_GetFlags(D_8014857A, D_801C893C[D_8014857A][D_8014857C]) & 0x20u) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
    } else {
        g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
    }
    g_BattleUIState        = 1;
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1;
}
