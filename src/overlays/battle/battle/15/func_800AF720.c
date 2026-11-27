#include "battle_15.h"

/* Scratchpad work-area pointer cell (0x1F800044); declared file-locally until
 * the shared declaration returns to battle_15.h. */

MATCH u32 func_800AF720(u32 start, u32 end, u32 value) {
    BattleRange* work;
    u32          half_value;
    /* FAKE: pin keeps result in v0, value in t0. */
    FAKE_REG(u32, result, "v0");
    u32 first;
    u32 second;

    result     = 0;
    half_value = value >> 1;
    work       = SELF(BattleRange);
    first      = work->range_x + half_value - start;
    second     = work->range_y + half_value - end;
    if (value >= first) {
        result = value >= second;
    }
    return result;
}
