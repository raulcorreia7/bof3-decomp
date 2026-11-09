#include "battle_03.h"

MATCH void func_801EA530(u8* active_flag, u32 arg1, u32 arg2, u32 arg3, s16* share, u8* budget, s16* counter, u8* clear_flag) {
    s16 counter_value;
    u8  budget_value;

    counter_value = *counter;
    budget_value  = *budget;
    if (counter_value < budget_value) {
        *budget = budget_value - counter_value;
    } else {
        *budget     = 0u;
        *clear_flag = 0u;
    }
    if ((*share != 0) && (*active_flag == 0u)) {
        *active_flag = 1u;
    }
}
