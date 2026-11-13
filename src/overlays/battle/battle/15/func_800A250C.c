#include "battle_15.h"

MATCH void func_800A250C(void) {
    u8 battler_index;
    u8 selection_kind;

    Battle_MarkDamageApplied();
    battler_index = g_BattleActiveBattler;
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    FAKE_ORDER_LOCK(selection_kind = g_BattleTarget);
    if (func_800A3B6C(battler_index, selection_kind, 0x80) == 0) {
        func_800A31E0(g_Battle.target, 8);
    }
}
