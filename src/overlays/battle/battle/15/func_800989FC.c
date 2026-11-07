#include "battle_15.h"

MATCH void func_800989FC(void) {
    u32 flags;

    flags = Item_GetFlags(D_8014857A, D_801C893C[D_8014857A][D_8014857C]);
    if ((flags & 0x40u) != 0u) {
        if ((flags & 0x10u) != 0u) {
            g_BattleUIStep = 5u;
        } else {
            g_BattleUIStep = 4u;
        }
        return;
    }
    if ((flags & 0x80u) != 0u) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_BOTH_SIDES;
    } else if ((flags & 0x10u) != 0u) {
        if ((flags & 0x20u) != 0u) {
            g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
        } else {
            g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
        }
    } else {
        g_BattleActorTurn->command.target = g_BattleMessageSlot[5];
    }
    g_BattleUIStep  = 4u;
    g_BattleUIState = 3u;
}
