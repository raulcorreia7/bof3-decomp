#include "battle_15.h"

MATCH u32 func_800AF66C(BattleRange* range, u32 extent) {
    u32          half_value;
    BattleRange* work;
    u32          first;
    u32          second;

    half_value = extent >> 1;
    work       = SELF(BattleRange);
    first      = work->range_x + half_value - range->range_x;
    second     = work->range_y + half_value - range->range_y;
    if (extent >= first && extent >= second)
        return 1;
    return 0;
}
