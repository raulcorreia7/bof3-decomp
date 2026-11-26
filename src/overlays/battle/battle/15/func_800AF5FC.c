#include "battle_15.h"

MATCH s32 func_800AF5FC(BattleRange* target, u32 extent) {
    /* FAKE: pin keeps result in v0. */
    FAKE_REG(s32, result, "v0");
    BattleRange* work;
    u32          half_value;
    u32          span;
    u32          first;
    u32          second;

    result     = 0;
    work       = SELF(BattleRange);
    span       = (work->unk3E + (extent >> 9)) - target->unk3E;
    half_value = extent >> 1;
    first      = work->range_x + half_value - target->range_x;
    second     = work->range_y + half_value - target->range_y;
    if (extent >= first && extent >= second) {
        result = (extent >> 8) >= (span & HALF_MASK);
    }
    return result;
}
