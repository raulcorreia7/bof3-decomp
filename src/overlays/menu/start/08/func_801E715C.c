#include "start_08.h"

MATCH u8 func_801E715C(s32 range_low, s32 range_high, s32 draw_count) {
    s32 range;
    s32 sum;
    u8  count;
    u8  i;

    sum   = 0;
    i     = 0;
    count = draw_count & 0xFF;
    if (count != 0) {
        range = ((range_high & 0xFF) - (range_low & 0xFF)) + 1;
        do {
            i++;
            sum += range_low + rand() % range;
        } while ((i & 0xFF) < count);
    }
    return sum;
}
