#include "battle_03.h"

/* clears the small local/enemy action scratch flags for one battler
 * and removes it from the ranked owner list if present.
 */
/* func_801DD14C */
MATCH void Battle_CancelTurn(u8 battler_index) {
    u8 index;

    if (BATTLER_IS_PLAYER(battler_index)) {
        g_Game.members[battler_index].u.turn.damage_flags.value &= ~COMBATANT_FLAG_DEFENDING;
        g_Game.members[battler_index].u.turn.command.type = 0u;
        g_Game.members[battler_index].u.turn.action_flags.value &= ~COMBATANT_FLAG_ABILITY_ALT_POSE;
    } else {
        u32 f                                                  = ENEMY_COMBATANT(battler_index).turn.damage_flags.value;
        ENEMY_COMBATANT(battler_index).turn.command.type       = 0u;
        ENEMY_COMBATANT(battler_index).turn.damage_flags.value = f & ~2u;
    }

    index = 0u;
    while (index < *(&g_BattleTurnCount)) {
        if (battler_index == g_BattleTurnOrder[index]) {
            g_BattleTurnOrder[index] = 0xFFu;
        }
        index += 1u;
    }
}
