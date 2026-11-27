#include "battle_15.h"

MATCH void func_8009EB28(void) {
    volatile u16* flagp;
    volatile u8*  battlerp;
    volatile u16* scaledp;
    u16           flag;
    u32           battler;
    u16           base;
    /* FAKE: retail keeps the loaded scaled halfword in v0. */
    FAKE_REG(s32, scaled, "v0");
    /* FAKE: retail keeps the shift result in v1. */
    FAKE_REG(s32, shifted, "v1");
    u8  battler_check;
    u8  selection;
    u32 enemy;
    s16 value;

    flagp   = &g_Battle.flags;
    flag    = *flagp;
    battler = g_Battle.active_battler;
    *flagp  = flag | BATTLE_STATE_DAMAGE_APPLIED;
    if (BATTLER_IS_PLAYER(battler)) {
        base                       = g_Game.members[battler].chr.stats.power;
        g_BattleCalcStats[1].power = base;
    } else {
        /* FAKE: retail computes the enemy row index in v0, the row offset in v1. */
        FAKE_REG(u32, enemy, "v0") = battler - 3;
        base                       = g_BattleEnemyBattlers[enemy].stats.power;
        g_BattleCalcStats[1].power = base;
    }
    battlerp                          = &g_Battle.active_battler;
    battler_check                     = *battlerp;
    scaledp                           = &g_BattleCalcStats[1].power;
    scaled                            = *scaledp;
    shifted                           = scaled >> 2;
    selection                         = g_Battle.target;
    *scaledp                          = scaled + shifted;
    value                             = Battle_CalcDamage(battler_check, selection, BATTLE_ELEMENT_FROM_WEAPON);
    g_Battle.target_record->hp_change = value;
    if (value != 0 && (Battle_PickAbility(*battlerp, g_Battle.target) & BYTE_MASK) == 0) {
        func_801DDFEC(g_Battle.target);
        func_801DD14C(g_Battle.target);
    }
}
