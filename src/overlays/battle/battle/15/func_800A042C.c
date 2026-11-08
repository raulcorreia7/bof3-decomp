#include "battle_15.h"

MATCH void func_800A042C(void) {
    u8  battler;
    u16 value;
    u8  battler_index;
    u8  selection_kind;
    /* FAKE: the retail enemy row index is in v0 and the offset chain in v1. */
    FAKE_REG(u32, enemy_index, "v0");

    battler = LOBU(g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(battler)) {
        value = g_Game.members[battler].chr.stats.power;
    } else {
        enemy_index = battler - 3u;
        value       = g_BattleEnemyBattlers[enemy_index].stats.power;
    }
    D_801EC30C = value;
    switch
        RANDOM_MASK(3) {
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
    battler_index  = g_Battle.active_battler;
    selection_kind = g_Battle.target;
    /* FAKE: the barrier keeps the kind materialization out of the case exits
     * so it lands last, in the jal delay slot as retail has it. */
    FAKE_BARRIER();
    g_Battle.target_record->hp_change = Battle_CalcDamage(battler_index, selection_kind, 0xFFFFU);
}
