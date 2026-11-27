#include "battle_15.h"

MATCH void func_8009FA20(void) {
    u8  battler;
    u16 value;
    /* FAKE: retail keeps the enemy index in v0 and the scaled row offset in v1. */
    FAKE_REG(u32, enemy_index, "v0");
    u8  battler_index;
    u8  selection_type;
    s16 res;

    battler = LOBU(g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(battler)) {
        value      = g_Game.members[battler].chr.stats.power;
        g_BattleCalcStats[1].power = value;
    } else {
        enemy_index = battler - 3u;
        value       = g_BattleEnemyBattlers[enemy_index].stats.power;
        g_BattleCalcStats[1].power  = value;
    }
    LOHU(g_BattleCalcStats[1].power)                  = LOHU(g_BattleCalcStats[1].power) * 80 / 100;
    battler_index                     = g_Battle.active_battler;
    selection_type                    = g_Battle.target;
    res                               = Battle_CalcDamage(battler_index, selection_type, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = res;
}
