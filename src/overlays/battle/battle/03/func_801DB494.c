#include "battle_03.h"

/* clears one local/enemy ranking scratch set across all battlers.
 */
MATCH void func_801DB494(void) {
    u8 index;

    index = 0u;
    while (index < 3u) {
        g_BattlePartyBattlers[index].mode_119           = 0u;
        g_BattlePartyBattlers[index].damage_flags.value = 0u;
        index += 1u;
    }

    index = 0u;
    while (index < 8u) {
        g_BattleEnemyBattlers[index].unk_F5       = 0u;
        g_BattleEnemyBattlers[index].damage_flags = 0u;
        index += 1u;
    }
}
