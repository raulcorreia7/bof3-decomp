#include "battle_15.h"

MATCH s32 func_800A4160(s32 selection_kind, s32 battler_index) {
    u8 kind;

    kind = selection_kind;
    if (func_800A3A10(g_Battle.active_battler, g_Battle.target) != 0) {
        return 1;
    }
    func_800A39B4((s8)battler_index, kind);
    Battle_RescaleStats(g_Battle.target);
    return 0;
}
