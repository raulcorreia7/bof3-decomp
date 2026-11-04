#include "shop_00.h"

MATCH s32 Shop_ApplyPercent(s32 value, s32 percent) {
    u32 scaled;

    scaled = (u32)(value * (percent & HALF_MASK)) / 100;
    if (scaled == 0) {
        scaled = 1;
    }
    return scaled;
}
