#include "battle_15.h"

MATCH s32 func_800A4160(s32 selection_type, s32 battler_index) {
    u8 type;

    type = selection_type;
    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) != 0) {
        return 1;
    }
    Battle_AddStatClamped((s8)battler_index, type);
    Battle_RescaleStats(g_Battle.target);
    return 0;
}
