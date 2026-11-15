#include "battle_15.h"

MATCH void func_800A2668(void) {
    volatile u8* battler;
    u8           battler_index;
    u8           selection_kind;
    s32          half;

    battler       = &g_BattleActiveBattler;
    battler_index = *battler;
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    FAKE_ORDER_LOCK(selection_kind = g_BattleTarget);
    half                              = Battle_CalcDamage(battler_index, selection_kind, BATTLE_ELEMENT_FROM_WEAPON) / 2;
    g_Battle.target_record->hp_change = half;
    if (half != 0 && Battle_PickAbility(*battler, g_Battle.target) == 0) {
        func_800A4238(4);
    }
}
