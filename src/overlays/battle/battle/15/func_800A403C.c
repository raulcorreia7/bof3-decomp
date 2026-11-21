#include "battle_15.h"

MATCH u8 func_800A403C(u8 battler_index) {
    u16 index;
    u8  saved;

    Battle_MarkDamageApplied();
    saved = battler_index;
    if (Battle_PickAbility(g_BattleActiveBattler, g_BattleTarget) != 0) {
        return 1;
    }
    index = g_BattleActionId;
    /* kept: the volatile table read changes the retail register schedule. */
    Battle_AddStatClamped((s8)((Ability*)g_Abilities)[index].power, saved);
    Battle_RescaleStats(g_Battle.target);
    return 0;
}
