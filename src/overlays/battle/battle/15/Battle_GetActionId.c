/* scales an attack's base damage by the battle damage rate and
 * variance percents, applies the active element rule modifier, a random
 * damage roll percent, and halving/voiding status flags of the target
 * battler before returning the final s16 damage.
 */
#include "battle_15.h"

/* func_800A2880 */
MATCH s16 Battle_GetActionId(u8 unused, u8 battler_index, u16 base_value, u8 element_flag) {
    u32 rate_scale;
    u32 rate_variance;
    s32 scale;
    s32 damage;
    s32 multiplier;
    s32 rule_mask;
    s16 element_mod;
    u32 roll;
    rate_scale = D_801EC312;
    scale      = (rate_scale + 100) * 100;
    damage     = (base_value * scale) / 100u;

    rate_variance = D_801EC2F2;
    multiplier    = 100 - (rate_variance / 5);
    if (multiplier < 50) {
        multiplier = 50;
    }
    damage    = (damage * multiplier) / 100u;
    rule_mask = D_801CA71C[g_Battle.action_id].mask & ELEM_ALL;
    if (rule_mask != 0) {
        if (element_flag != 0) {
            element_mod = func_800A2EF0(battler_index, rule_mask);
        } else {
            element_mod = Battle_GetFireResistance(battler_index, rule_mask);
        }
        damage = (damage * element_mod) / 100;
    }

    roll   = RANDOM_MASK(7);
    damage = (damage * D_800B492C[roll]) / 10000;

    if ((BATTLER_IS_PLAYER(g_Battle.target)) && (g_PartyFormation == 2) && (damage > 0)) {
        damage -= damage >> 2;
    }

    if (BATTLER_IS_PLAYER(battler_index)) {
        if (g_Game.members[battler_index].u.turn.action_flags.value & COMBATANT_FLAG_DAMAGE_HALVED) {
            damage /= 2;
        }
        if (g_Game.members[battler_index].u.turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            damage = 0;
        }
    } else {
        if (g_BattleEnemyBattlers[battler_index - 3u].turn.action_flags.value & COMBATANT_FLAG_DAMAGE_HALVED) {
            damage /= 2;
        }
        if (g_BattleEnemyBattlers[battler_index - 3u].turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            damage = 0;
        }
    }

    return damage;
}
