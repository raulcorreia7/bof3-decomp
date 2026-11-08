#include "start_08.h"

MATCH u8 func_801E715C(s32 range_low, s32 range_high, s32 draw_count) {
    s32 range;
    s32 sum;
    u8  count;
    u8  i;

    sum   = 0;
    i     = 0;
    count = draw_count & BYTE_MASK;
    if (count != 0) {
        range = ((range_high & BYTE_MASK) - (range_low & BYTE_MASK)) + 1;
        do {
            i++;
            sum += range_low + RANDOM_MOD(range);
        } while ((i & BYTE_MASK) < count);
    }
    return sum;
}
