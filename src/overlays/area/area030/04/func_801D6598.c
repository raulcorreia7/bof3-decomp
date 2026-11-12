#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Seeds the AREA030 scratch record for the later menu phase, clears
 * its panel state, bumps scratch state byte `0x03` and arms mode 3. */
MATCH void func_801D6598(void) {
    FishingState* record;
    FishingState* retired;
    FishingState* tail;

    Area_SelectSceneRecord(0x47);
    FISHING_STATE->active_flags = 0x80;
    FISHING_STATE->state_29     = 1;
    FISHING_STATE->state_2A     = 0;

    record              = FISHING_STATE;
    record->counter_48  = 0;
    retired             = FISHING_STATE;
    record->origin_x_2E = 0xCA;
    record->origin_y_30 = 0xBA;
    retired->tint_5D    = 0;

    FISHING_STATE->tint_5E        = 0;
    FISHING_STATE->tint_5F        = 0;
    FISHING_STATE->step_timer_09  = 0;
    FISHING_STATE->step_index_0A  = 0;
    FISHING_STATE->saved_index_0B = 0;

    tail               = FISHING_STATE;
    tail->sub_index_03 = (tail->sub_index_03 + 1);
    Actor_SelectScript(3);
}
