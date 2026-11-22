#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase, clears
 * its panel state and bumps scratch state byte `0x03`. */
MATCH void func_801D6044(void) {
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
    record->origin_x   = 0xF0;
    record->origin_y   = 0xC2;
    retired->tint_5D   = 0;

    TASK(FishingState)->tint_5E    = 0;
    TASK(FishingState)->tint_5F    = 0;
    TASK(FishingState)->timer      = 0;
    TASK(FishingState)->step_index = 0;
    TASK(FishingState)->cue_index  = 0;

    tail            = TASK(FishingState);
    tail->sub_index = (tail->sub_index + 1);
}
