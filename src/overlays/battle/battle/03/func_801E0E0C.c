#include "battle_03.h"

/* reports whether all active local battlers satisfy the strict ready
 * predicate used by the later queued branch.
 */
MATCH u8 func_801E0E0C(void) {
    u8 index;

    for (index = 0u; index < BATTLE_PARTY_CHARACTERS_COUNT; index += 1u) {
        u16 flags_80;

        if (!ACTOR_IN_USE(g_BattlePartyBattlers[index])) {
            continue;
        }
        flags_80 = g_BattlePartyBattlers[index].chr.status;
        if ((flags_80 & (STATUS_PARALYZED | STATUS_KO)) == 0u) {
            return 0u;
        }
        if ((g_BattlePartyBattlers[index].turn.damage_flags.value & COMBATANT_FLAG_WILLPOWER_SURVIVED) != 0u) {
            return 0u;
        }
        if ((g_BattlePartyBattlers[index].turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) != 0u) {
            return 0u;
        }
        if ((flags_80 & STATUS_KO) != 0u) {
            if (g_BattlePartyBattlers[index].chr.equip.accessories[0] == ACCESSORY_SOUL_GEM) {
                return 0u;
            }
            if (g_BattlePartyBattlers[index].chr.equip.accessories[1] == ACCESSORY_SOUL_GEM) {
                return 0u;
            }
            if (g_BattlePartyBattlers[index].chr.equip.armor == ARMOR_MANLY_CLOTHES) {
                return 0u;
            }
        }
    }
    return 1u;
}
