#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase, clears
 * its panel state and bumps scratch state byte `0x03`. */
MATCH void func_801D5C8C(void) {
    FishingState* record;
    FishingState* retired;
    FishingState* tail;
    FishingState* state;

    Area_SceneSelectRecord(0x47);
    SELF(FishingState)->active_flags = 0x80;
    SELF(FishingState)->state_29     = 1;
    SELF(FishingState)->state_2A     = 0;

    record             = SELF(FishingState);
    record->counter_48 = 0;
    retired            = SELF(FishingState);
    record->origin_x   = 0xEC;
    record->origin_y   = 0xA2;
    retired->tint_5D   = 0;

    SELF(FishingState)->tint_5E    = 0;
    SELF(FishingState)->tint_5F    = 0;
    SELF(FishingState)->timer      = 0;
    SELF(FishingState)->step_index = 0;
    SELF(FishingState)->cue_index  = 0;

    tail             = SELF(FishingState);
    tail->cue_index  = 0;
    state            = SELF(FishingState);
    tail->pos_x      = 0;
    tail->step_delta = 4;
    state->sub_index = (state->sub_index + 1);
}
