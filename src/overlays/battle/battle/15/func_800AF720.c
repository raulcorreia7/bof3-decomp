#include "battle_15.h"

/* Scratchpad work-area pointer cell (0x1F800044). */

MATCH u32 func_800AF720(u32 start, u32 end, u32 value) {
    BattleRange* work;
    u32          half_value;
    /* FAKE: pin keeps result in v0, value in t0. */
    FAKE_REG(u32, result, "v0");
    u32 first;
    u32 second;

    result     = 0;
    half_value = value >> 1;
    work       = (BattleRange*)g_Task;
    first      = work->range_axis_34 + half_value - start;
    second     = work->range_axis_38 + half_value - end;
    if (value >= first) {
        result = value >= second;
    }
    return result;
}
