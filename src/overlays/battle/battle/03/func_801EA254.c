#include "battle_03.h"

/* The bar's scale byte runs over this many steps of the 0x10-pixel bar. */
#define BATTLE_BAR_SCALE_MAX  55
/* The scale byte that marks a full bar. */
#define BATTLE_BAR_SCALE_FULL 0x38
/* Each step of the bar animation covers this many scale steps. */
#define BATTLE_BAR_STEP_SHIFT 4
/* The step count is rounded up to this many scale steps. */
#define BATTLE_BAR_STEP_ROUND 0xF

MATCH void func_801EA254(u8* scale, s16* max_value, s16* last_max, s16* value, s16* target, u8* delta, s16* steps,
                         s8* direction) {
    if (*last_max != *max_value) {
        if (*target >= *max_value) {
            *target = *max_value;
        }
        if (*value == *target) {
            *scale = (*value * BATTLE_BAR_SCALE_MAX / *max_value);
            if (*target != 0 && *scale == 0) {
                *scale = 1;
            }
        } else {
            *scale = (*value * BATTLE_BAR_SCALE_MAX / *max_value);
            if (*scale >= BATTLE_BAR_SCALE_FULL) {
                *scale = BATTLE_BAR_SCALE_MAX;
                *value = *target;
            }
        }
        *last_max = *max_value;
    }
    if (*value > *target) {
        if (*target == 0) {
            *delta = *scale;
            *scale = 0;
        } else {
            SP_REF(u8, 0x0) = *scale;
            *scale          = (*target * BATTLE_BAR_SCALE_MAX / *max_value);
            if (*target != 0 && *scale == 0) {
                *scale = 1;
            }
            *delta = SP_REF(u8, 0x0) - *scale;
        }
        *steps     = *delta >> BATTLE_BAR_STEP_SHIFT;
        *direction = 1;
    } else if (*value < *target) {
        s32 step;

        step = (*target * BATTLE_BAR_SCALE_MAX / *max_value) - (*value * BATTLE_BAR_SCALE_MAX / *max_value);
        if (step < 0) {
            step += BATTLE_BAR_STEP_ROUND;
        }
        *steps     = step >> BATTLE_BAR_STEP_SHIFT;
        *direction = 2;
    } else {
        return;
    }
    if (*steps == 0) {
        *steps = 1;
    }
    *value = *target;
}
