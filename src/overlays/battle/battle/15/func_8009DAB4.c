#include "battle_15.h"

/* FAKE: the call arguments are read into locals first and the barrier keeps the
 * kind-0xFFFF materialization out of the load-delay path, so it lands in the
 * jal delay slot as retail has it.
 */
MATCH void func_8009DAB4(void) {
    /* FAKE: retail keeps the enemy row index in v0. */
    MATCH_REG(u32, enemy_index, "v0");
    u8  battler;
    u16 value;
    u8  battler_index;
    u8  selection_kind;
    s16 res;

    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        value = g_BattlePartyBattlers[battler].chr.stats.power;
    } else {
        enemy_index = battler - 3u;
        value       = g_BattleEnemyBattlers[enemy_index].stats.power;
    }
    D_801EC30C = value;
    switch (RANDOM_MASK(3)) {
        case 0: {
            u16* cell = (u16*)&D_801EC30C;
            *cell     = (*cell >> 1);
            break;
        }
        case 3: {
            volatile u16* cell = &D_801EC30C;
            u16           half = *cell;
            *cell              = half + (half >> 1);
            break;
        }
    }
    battler_index  = g_BattleActiveBattler;
    selection_kind = g_BattleTarget;
    /* FAKE: keeps the 0xFFFF load in the jal delay slot. */
    MATCH_FAKE_BARRIER();
    res                             = Battle_CalcDamage(battler_index, selection_kind, 0xFFFF);
    g_BattleTargetRecord->hp_change = res;
}
