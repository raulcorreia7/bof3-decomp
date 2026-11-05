#include "battle_03.h"

MATCH u8 func_801DB3E4(u32 battler_index, u32 average_threshold, u32 max_threshold) {
    u16 value;
    int threshold;
    /* FAKE: pin the scaled row offset to v1 so the load keeps v1. */
    MATCH_REG(u32, offset, "v1");

    threshold     = average_threshold & HALF_MASK;
    battler_index = (battler_index & BYTE_MASK) - 3u;
    offset        = battler_index * 280u;
    value         = FIELD(u16, &D_801EB630[0].stats.agility, offset);
    if ((threshold << 1) <= value) {
        return value >= (max_threshold & HALF_MASK);
    }
    return 0;
}
