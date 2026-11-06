#include "battle_15.h"

MATCH void func_800A2668(void) {
    volatile u8* battler;
    u8           battler_index;
    u8           selection_kind;
    s32          half;

    battler       = &g_BattleActiveBattler;
    battler_index = *battler;
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    ORDER_LOCK(selection_kind = g_BattleTarget);
    half                            = Battle_CalcDamage(battler_index, selection_kind, 0xFFFF) / 2;
    g_BattleTargetRecord->hp_change = half;
    if (half != 0 && func_800A3A10(*battler, g_BattleTarget) == 0) {
        func_800A4238(4);
    }
}
