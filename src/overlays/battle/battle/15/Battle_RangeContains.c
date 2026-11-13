#include "battle_15.h"

/* func_800AF66C */
MATCH u32 Battle_RangeContains(BattleRange* range, u32 extent) {
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
    work       = (BattleRange*)g_Task;
    first      = work->range_axis_34 + half_value - range->range_axis_34;
    second     = work->range_axis_38 + half_value - range->range_axis_38;
    if (value >= first) {
        result = value >= second;
    }
    return result;
}
