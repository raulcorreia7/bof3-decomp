#include "battle_15.h"

/* scans the three local battler slots (0x140 stride) and enemy slots 3-10 (0x118 stride) for an entry with
 * its +0x00 flag and damage-status nibble 0xF0 both set; returns 1 if one exists, else 0.
 */
MATCH s32 func_800A99AC(void) {
    u8 i;

    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (ACTOR_IN_USE(g_Game.members[i]) &&
            (g_Game.members[i].u.turn.damage_flags.value & (COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED | COMBATANT_FLAG_DAMAGE_NUMBER)) != 0u) {
            return 1;
        }
    }

    for (i = 3; i < COMBATANT_COUNT; i++) {
        u32 index = (i - 3);

        if ((g_BattleEnemyBattlers[index].header.flags & 0x1u) != 0u &&
            (g_BattleEnemyBattlers[index].turn.damage_flags.value & (COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED | COMBATANT_FLAG_DAMAGE_NUMBER)) != 0u) {
            return 1;
        }
    }

    return 0;
}
