#include "battle_15.h"

MATCH void func_800A042C(void) {
    u8  battler;
    u16 value;
    u8  battler_index;
    u8  selection_kind;
    /* FAKE: the retail enemy row index is in v0 and the offset chain in v1. */
    MATCH_FAKE_PIN(u32, enemy_index, "v0");

    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        value = g_BattlePartyBattlers[battler].stats.stats.power;
    } else {
        enemy_index = battler - 3u;
        value       = D_801EB630[enemy_index].attack;
    }
    D_801EC30C = value;
    switch (RANDOM_MASK(3)) {
        case 0:
            LOHU(D_801EC30C) >>= 1;
            break;
        case 1:
            LOHU(D_801EC30C) = LOHU(D_801EC30C);
            break;
        case 2:
            LOHU(D_801EC30C) += LOHU(D_801EC30C) >> 1;
            break;
        default:
            LOHU(D_801EC30C) *= 2;
            break;
    }
    battler_index  = g_BattleActiveBattler;
    selection_kind = g_BattleTarget;
    /* FAKE: the barrier keeps the kind materialization out of the case exits
     * so it lands last, in the jal delay slot as retail has it. */
    MATCH_FAKE_BARRIER();
    ((s16*)g_BattleTargetRecord)[2] = Battle_CalcDamage(battler_index, selection_kind, 0xFFFFU);
}
