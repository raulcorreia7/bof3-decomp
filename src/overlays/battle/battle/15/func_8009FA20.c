#include "battle_15.h"

MATCH void func_8009FA20(void) {
    u8  battler;
    u16 value;
    /* FAKE: retail keeps the enemy index in v0 and the scaled row offset in v1. */
    MATCH_REG(u32, enemy_index, "v0");
    u8  battler_index;
    u8  selection_kind;
    s16 res;

    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        value = g_BattlePartyBattlers[battler].chr.stats.power;
    } else {
        enemy_index = battler - 3u;
        value       = D_801EB630[enemy_index].attack;
    }
    D_801EC30C = value;
    /* FAKE: keeps the retail store before the scaled view's address setup. */
    MATCH_FAKE_BARRIER();
    LOHU(D_801EC30C) = LOHU(D_801EC30C) * 80 / 100;
    battler_index    = g_BattleActiveBattler;
    selection_kind   = g_BattleTarget;
    /* FAKE: keeps the whole-mask argument out of the load-delay path so
     * it lands in the jal delay slot as retail has it. */
    MATCH_FAKE_BARRIER();
    res                             = Battle_CalcDamage(battler_index, selection_kind, 0xFFFF);
    ((s16*)g_BattleTargetRecord)[2] = res;
}
