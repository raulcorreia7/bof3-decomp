#include "battle_03.h"

MATCH s16 func_801DE144(s32 amount, s32 percent) {
    s32 value;

    value = (amount * percent) / 100;
    if (value >= 101) {
        value = 100;
    }
    CLAMP_MIN(value, 0);
    return value;
}
