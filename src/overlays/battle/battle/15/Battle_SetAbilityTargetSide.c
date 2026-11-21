#include "battle_15.h"

/* func_80097D58 */
MATCH void Battle_SetAbilityTargetSide(void) {
    u16 kind;

    kind = g_BattleActorTurn->command.id;
    if ((g_Abilities[kind].targeting_flags & ABILITY_TARGET_FLAG_OPPONENT) != 0) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
    } else {
        g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
    }
    g_Battle.ui_mode         = 1;
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1;
}
