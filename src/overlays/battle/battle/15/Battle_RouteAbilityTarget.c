#include "battle_15.h"

/* func_8009761C */
MATCH void Battle_RouteAbilityTarget(void) {
    u8* entry;
    u8  flags;

    entry = Party_GetAbilities(D_80148656, g_UIPanelTasks[16].unk_0B, 1);
    flags = g_Abilities[entry[g_UIPanelTasks[16].unk_0C]].targeting_flags;
    if ((flags & ABILITY_TARGET_FLAG_SELECT) != 0u) {
        if ((flags & ABILITY_TARGET_FLAG_ALL) != 0u) {
            g_Battle.ui_step = 5u;
        } else {
            g_Battle.ui_step = 4u;
        }
        return;
    }
    if ((flags & ABILITY_TARGET_FLAG_BOTH_SIDES) != 0u) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_BOTH_SIDES;
    } else if ((flags & ABILITY_TARGET_FLAG_ALL) != 0u) {
        if ((flags & ABILITY_TARGET_FLAG_OPPONENT) != 0u) {
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
