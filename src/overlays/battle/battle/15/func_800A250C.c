#include "battle_15.h"

MATCH void func_800A250C(void) {
    u8 battler_index;
    u8 selection_type;

    Battle_MarkDamageApplied();
    battler_index = g_BattleActiveBattler;
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    do {
        selection_type = g_BattleTarget;
    } while (0);
    if (func_800A3B6C(battler_index, selection_type, 0x80) == 0) {
        Battle_AddStatus(g_Battle.target, 8);
    }
}
