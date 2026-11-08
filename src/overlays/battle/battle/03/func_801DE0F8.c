#include "battle_03.h"

MATCH s16 func_801DE0F8(s32 base, s32 percent) {
    s32 value;

    value = (base * percent) / 100;
    if (value >= 10000) {
        value = 9999;
    }
    CLAMP_MIN(value, 0);
    return value;
}
