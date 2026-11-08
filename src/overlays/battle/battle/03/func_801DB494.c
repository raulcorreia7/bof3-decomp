#include "battle_03.h"

/* clears one local/enemy ranking scratch set across all battlers.
 */
MATCH void func_801DB494(void) {
    u8 index;

    index = 0u;
    while (index < 3u) {
        g_BattlePartyBattlers[index].u.turn.command.type       = 0u;
        g_BattlePartyBattlers[index].u.turn.damage_flags.value = 0u;
        index += 1u;
    }

    index = 0u;
    while (index < 8u) {
        g_BattleEnemyBattlers[index].turn.command.type       = 0u;
        g_BattleEnemyBattlers[index].turn.damage_flags.value = 0u;
        index += 1u;
    }
}
