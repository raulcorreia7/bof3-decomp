#include "battle_15.h"

/* Player flag rows (stride 0x140) and enemy flag rows (stride 0x118) hold the
 * byte read here at record offset 0. */

MATCH s16 func_800A3060(u8 battler_index, u16 rule_mask) {
    u8  index;
    s32 value;

    value = 0;
    if (BATTLER_IS_PLAYER(battler_index)) {
        if (rule_mask & 0x20u) {
            index = g_BattlePartyBattlers[battler_index].chr.stats.resistances[RES_SLOT_HOLY];
            value = D_800B496C[index];
        }
    } else if (rule_mask & 0x20u) {
        index = ENEMY_COMBATANT(battler_index).stats.resistances[RES_SLOT_HOLY];
        value = D_800B496C[index];
    }
    return value;
}
