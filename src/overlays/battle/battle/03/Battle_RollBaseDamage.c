#include "battle_03.h"

MATCH u32 Battle_RollBaseDamage(u8 attacker, u8 target, u8 skip_reduction) {
    s32 damage;
    s32 band;

    if (attacker < PARTY_SLOT_COUNT) {
        s32 base = D_801EC30C;

        if (skip_reduction == 0)
            damage = base - D_801EC2EE;
        else
            damage = base;
        if (damage < 0)
            damage = 0;
        damage += rand() & 1;
    } else if (target < PARTY_SLOT_COUNT) {
        s32 base = D_801EC30C;

        if (skip_reduction == 0)
            damage = base - (func_801DCCB0() & HALF_MASK);
        else
            damage = base;
        if (damage < 0)
            damage = 0;
        band = damage / -5;
        if (damage >= -4)
            band = 0;
        if (damage < -0x33)
            band = 8;
        damage <<= 8;
        damage += (ENEMY_COMBATANT(attacker).power << 8) * (((rand() % 2) + 2) << 8) /
                  (s_BattleDamageBandDivisors[band & BYTE_MASK] << 8);
        damage >>= 8;
        damage += rand() & 1;
    } else {
        s32 base = D_801EC30C;

        if (skip_reduction == 0)
            damage = base - D_801EC2EE;
        else
            damage = base;
        if (damage < 0)
            damage = 0;
        damage += rand() & 1;
    }
    return (s16)(func_801DCD50(attacker, target, damage));
}
