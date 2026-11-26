#include "battle_15.h"

MATCH u32 func_800AF66C(BattleRange* range, u32 extent) {
    /* FAKE: pin keeps result in v0 on entry. */
    FAKE_REG(u32, result, "v0");
    u32          value;
    u32          half_value;
    BattleRange* work;
    u32          first;
    u32          second;

    value      = extent;
    result     = 0;
    half_value = value >> 1;
    work       = SELF(BattleRange);
    first      = work->range_x + half_value - range->range_x;
    second     = work->range_y + half_value - range->range_y;
    if (value >= first) {
        result = value >= second;
    }
    return result;
}
