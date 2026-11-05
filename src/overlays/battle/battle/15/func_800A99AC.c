#include "battle_15.h"

/* scans the three local battler slots (0x140 stride) and enemy slots 3-10 (0x118 stride) for an entry with
 * its +0x00 flag and damage-status nibble 0xF0 both set; returns 1 if one exists, else 0.
 */
MATCH s32 func_800A99AC(void) {
    u8 i;

    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        if (ACTOR_IN_USE(g_BattlePartyBattlers[i]) && (g_BattlePartyBattlers[i].damage_flags.value & 0xF0u) != 0u) {
            return 1;
        }
    }

    for (i = 3; i < COMBATANT_COUNT; i++) {
        u32 index = (u32)(i - 3);

        if ((D_801EB630[index].flags & 1u) != 0u && (D_801EB630[index].damage_flags & 0xF0u) != 0u) {
            return 1;
        }
    }

    return 0;
}
