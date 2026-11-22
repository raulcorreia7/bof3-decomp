#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Seeds the AREA030 scratch record for the later menu phase, clears
 * its panel state, bumps scratch state byte `0x03` and arms mode 3. */
MATCH void func_801D6598(void) {
    FishingState* record;
    FishingState* retired;
    FishingState* tail;

    Area_SceneSelectRecord(0x47);
    TASK(FishingState)->active_flags = 0x80;
    TASK(FishingState)->state_29     = 1;
    TASK(FishingState)->state_2A     = 0;

    record             = TASK(FishingState);
    record->counter_48 = 0;
    retired            = TASK(FishingState);
    record->origin_x   = 0xCA;
    record->origin_y   = 0xBA;
    retired->tint_5D   = 0;

    TASK(FishingState)->tint_5E     = 0;
    TASK(FishingState)->tint_5F     = 0;
    TASK(FishingState)->step_timer  = 0;
    TASK(FishingState)->step_index  = 0;
    TASK(FishingState)->saved_index = 0;

    tail            = TASK(FishingState);
    tail->sub_index = (tail->sub_index + 1);
    Script_Select(3);
}
