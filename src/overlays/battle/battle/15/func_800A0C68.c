#include "battle_15.h"

/* sums the weighted affinity of each battle slot and stores the
 *           clamped result in the active record's halfword field.
 */
MATCH void func_800A0C68(void) {
    /* FAKE: retail reserves 8 stack bytes that no statement uses. */
    STACK_PADS(u8, 8);
    u8* p;
    u8* base;
    s32 total;
    MATCH_REG(u8, i, "s2");
    s32 weight;
    /* FAKE: pin the divided increment to retail v0. */
    MATCH_REG(s32, value, "v0");

    p     = (u8*)&D_801463D6;
    i     = 0;
    total = 0;
    if (*p != 0) {
        base = p - 0x62;
        do {
            weight = 3;
            if (i < 7) {
                weight = D_800B4924[i];
            }
            value = (Battle_CalcDamage(base[0], base[0x20], BATTLE_ELEMENT_FROM_WEAPON) * weight) / 10;
            total += value;
            i++;
        } while (i < base[0x62]);
    }
    if (total >= 10000) {
        total = 9999;
    }
    if (total < -9999) {
        total = -9999;
    }
    g_BattleTargetRecord->hp_change = total;
}
