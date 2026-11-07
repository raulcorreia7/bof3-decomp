#include "battle_15.h"

MATCH void func_8009761C(void) {
    u8* entry;
    u8  flags;

    entry = Party_GetAbilities(D_80148656, g_MenuPanelTasks[16].unk_0B, 1);
    flags = D_801CA718[entry[g_MenuPanelTasks[16].unk_0C] * 0x14];
    if ((flags & ABILITY_TARGET_SELECT) != 0u) {
        if ((flags & ABILITY_TARGET_ALL) != 0u) {
            g_BattleUIStep = 5u;
        } else {
            g_BattleUIStep = 4u;
        }
        return;
    }
    if ((flags & ABILITY_TARGET_BOTH_SIDES) != 0u) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_BOTH_SIDES;
    } else if ((flags & ABILITY_TARGET_ALL) != 0u) {
        if ((flags & ABILITY_TARGET_OPPONENT) != 0u) {
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
