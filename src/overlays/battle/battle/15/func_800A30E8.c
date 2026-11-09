#include "battle_15.h"

/* Player flag rows (stride 0x140) and enemy flag rows (stride 0x118) hold the battler's heal-resistance byte at record offset 0. */

/* Selection-kind flag table: the power byte at +0 of each 0x14-byte record. */
extern u8 D_801CA71B[];

MATCH s32 func_800A30E8(u8 unused, u8 battler_index) {
    u8  power;
    u8  resistance;
    u32 rate;
    s32 scale;
    s32 damage;

    rate   = D_801EC312 + 100;
    power  = D_801CA71B[g_Battle.action_id * 0x14];
    scale  = rate * 100;
    damage = (power * scale) / 100u;

    if (BATTLER_IS_PLAYER(battler_index)) {
        resistance = g_Game.members[battler_index].chr.stats.resistances[RES_INDEX_HOLY];
    } else {
        resistance = ENEMY_COMBATANT(battler_index).stats.resistances[RES_INDEX_HOLY];
    }

    damage = (damage * D_800B497C[resistance]) / 10000;
    return (s16)-damage;
}
