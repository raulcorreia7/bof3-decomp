#include "battle_03.h"

MATCH u32 Battle_RollBaseDamage(u8 attacker_slot, u8 target_slot, u8 skip_reduction) {
    s32 damage;
    s32 band;

    if (attacker_slot < PARTY_SLOT_COUNT) {
        s32 base = g_BattleCalcStats[1].power;

        if (skip_reduction == 0)
            damage = base - g_BattleCalcStats[0].defense;
        else
            damage = base;
        if (damage < 0)
            damage = 0;
        damage += RANDOM_MASK(1);
    } else if (target_slot < PARTY_SLOT_COUNT) {
        s32 base = g_BattleCalcStats[1].power;

        if (skip_reduction == 0)
            damage = base - (Battle_CalcPartyDefense() & HALF_MASK);
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
        damage += (ENEMY_COMBATANT(attacker_slot).level << 8) * (((RANDOM_MOD(2)) + 2) << 8) / (s_BattleDamageBandDivisors[band & BYTE_MASK] << 8);
        damage >>= 8;
        damage += RANDOM_MASK(1);
    } else {
        s32 base = g_BattleCalcStats[1].power;

        if (skip_reduction == 0)
            damage = base - g_BattleCalcStats[0].defense;
        else
            damage = base;
        if (damage < 0)
            damage = 0;
        damage += RANDOM_MASK(1);
    }
    return (s16)(Battle_ScaleDamage(attacker_slot, target_slot, damage));
}
