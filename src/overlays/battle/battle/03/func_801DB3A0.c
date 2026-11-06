#include "battle_03.h"

MATCH u8 func_801DB3A0(u32 battler_index, u32 average_threshold, u32 max_threshold) {
    u16 value;
    int threshold;
    /* FAKE: pin the scaled row offset to v1 so the load keeps v1. */
    MATCH_REG(u32, offset, "v1");

    threshold = average_threshold & 0xFFFF;
    battler_index &= 0xFF;
    offset = battler_index * 320u;
    value  = FIELD(u16, &g_BattlePartyBattlers[0].chr.stats.agility, offset);
    if ((threshold << 1) <= value) {
        return value >= (max_threshold & 0xFFFF);
    }
    return 0;
}
