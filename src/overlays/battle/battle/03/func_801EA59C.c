#include "battle_03.h"

MATCH void func_801EA59C(u8* counter, s16* budget_max, u32 arg2, u32 arg3, s16* share, u8* budget, s16* step, u8* clear_flag) {
    s32 limit;
    s16 step_value;
    u8  counter_value;

    limit         = (*share * 0x37) / *budget_max;
    step_value    = *step;
    counter_value = *counter;
    if (counter_value < (limit - step_value)) {
        *counter = step_value + counter_value;
    } else {
        *counter    = limit;
        *clear_flag = 0u;
    }
    if ((*share != 0) && (*counter == 0u)) {
        *counter = 1u;
    }
}
