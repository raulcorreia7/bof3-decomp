#include "battle_15.h"

MATCH u32 func_800AF720(u32 start, u32 end, u32 value) {
    BattleRange* work;
    u32          half_value;
    u32          first;
    u32          second;

    half_value = value >> 1;
    work       = SELF(BattleRange);
    first      = work->range_x + half_value - start;
    second     = work->range_y + half_value - end;
    if (value >= first && value >= second) {
        return 1;
    }
    return 0;
}
