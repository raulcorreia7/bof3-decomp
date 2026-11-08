#include "battle_15.h"

s16 func_800A2D70(u8 battler_index, u16 element_mask);

MATCH u8 func_800A3DF8(u8 battler_index, u8 selection_kind) {
    s32 rate;
    s32 threshold;
    s32 rollSeed;
    s16 temp;
    u8  ret;

    rollSeed  = *(u16*)&D_801EC312;
    threshold = (rollSeed / 5) + BATTLE_HIT_THRESHOLD_BASE;
    if (threshold >= BATTLE_HIT_THRESHOLD_MAX + 1) {
        threshold = BATTLE_HIT_THRESHOLD_MAX;
    }
    rate = *(u16*)&D_801EC2F2;
    rate = BATTLE_HIT_RATE_BASE - (rate / 5);
    CLAMP_MIN(rate, BATTLE_HIT_RATE_MIN);
    temp = func_800A2D70((selection_kind & BYTE_MASK), ELEM_STATUS);
    if (temp == -1) {
        ret = 0;
    } else {
        ret = (rand() % 100) >= ((threshold * rate * temp) / 10000);
    }
    return ret;
}
