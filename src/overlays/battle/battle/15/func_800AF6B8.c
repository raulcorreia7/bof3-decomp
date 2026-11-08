#include "battle_15.h"

MATCH u32 func_800AF6B8(u32 axis_34_bound, u32 axis_38_bound, s32 packed_span, u32 extent) {
    /* FAKE: pin keeps result in v0. */
    FAKE_REG(u32, result, "v0");
    BattleRange* work;
    u32          half_value;
    u32          span;
    u32          first;
    u32          second;

    result     = 0;
    work       = (BattleRange*)g_Task;
    span       = (work->unk3E + (extent >> 9)) - (packed_span >> 16);
    half_value = extent >> 1;
    first      = work->range_axis_34 + half_value - axis_34_bound;
    second     = work->range_axis_38 + half_value - axis_38_bound;
    if (extent >= first && extent >= second) {
        result = (extent >> 8) >= (span & HALF_MASK);
    }
    return result;
}
