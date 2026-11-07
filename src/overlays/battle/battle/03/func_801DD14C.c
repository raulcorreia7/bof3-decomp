#include "battle_03.h"

/* clears the small local/enemy action scratch flags for one battler
 * and removes it from the ranked owner list if present.
 */
MATCH void func_801DD14C(u8 battler_index) {
    u8 index;

    if (BATTLER_IS_PLAYER(battler_index)) {
        g_BattlePartyBattlers[battler_index].turn.damage_flags.value &= ~COMBATANT_FLAG_DEFENDING;
        g_BattlePartyBattlers[battler_index].turn.command.type = 0u;
        g_BattlePartyBattlers[battler_index].turn.action_flags.value &= ~COMBATANT_FLAG_ABILITY_ALT_POSE;
    } else {
        u32 f                                                  = ENEMY_COMBATANT(battler_index).turn.damage_flags.value;
        ENEMY_COMBATANT(battler_index).turn.command.type       = 0u;
        ENEMY_COMBATANT(battler_index).turn.damage_flags.value = f & ~2u;
    }

    index = 0u;
    while (index < *(&D_80146323)) {
        if (battler_index == (&D_8014630C)[index]) {
            (&D_8014630C)[index] = 0xFFu;
        }
        index += 1u;
    }
}
