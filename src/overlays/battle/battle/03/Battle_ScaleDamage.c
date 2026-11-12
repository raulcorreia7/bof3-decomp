#define GAME_SCRATCH_BASE_SCALAR
#include "battle_03.h"

/* Record views: the scale-index byte sits at record offset 0xA4 of the local
 * work array (stride 0x140) and at record offset 0xB4 of the enemy work array
 * (stride 0x118). */

/* func_801DCD50 */
MATCH u32 Battle_ScaleDamage(u32 unused, u8 battler_index, s32 damage_value) {
    s32  value;
    s32  damage;
    u32  slot;
    u16* scratch;
    /* FAKE: pins the first flag read to a1. */
    FAKE_REG(u16, flags, "a1");
    /* FAKE: pins the masked flag value to v0. */
    FAKE_REG(u16, mask, "v0");
    s16 element;

    damage = damage_value << 8;
    value  = (0x100 - ((damage / 0x3E800) << 17)) >> 8;
    CLAMP_MIN(value, 0xCD);
    scratch = (u16*)D_1F800000;
    damage  = ((damage * value) >> 8) * D_801EAFA0[RANDOM_MASK(7u)] >> 8;
    flags   = *scratch;
    mask    = flags & 0x1Fu;
    if (mask != 0u) {
        element = func_800A2AE0(battler_index);
        damage  = (damage * element) / 100;
    }
    if ((*scratch & 0x20u) != 0u) {
        if (BATTLER_IS_PLAYER(battler_index)) {
            damage = (damage * D_801EAFC0[g_Game.members[battler_index].chr.stats.resistances[RES_INDEX_HOLY]]) / 100;
        } else {
            slot   = battler_index - 3u;
            damage = (damage * D_801EAFC0[g_BattleEnemyBattlers[slot].stats.resistances[RES_INDEX_HOLY]]) / 100;
        }
    }

    if ((damage & BYTE_MASK) >= 0x80) {
        damage += 256;
    }
    return ((damage << 8) >> 16);
}
