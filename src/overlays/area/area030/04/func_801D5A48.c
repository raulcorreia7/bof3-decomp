#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase, clears
 * its panel state and bumps scratch state byte `0x03`. */
MATCH void func_801D5A48(void) {
    FishingState* record;
    FishingState* retired;
    FishingState* tail;

    Area_SceneSelectRecord(0x21);
    SELF(FishingState)->active_flags = 0x80;
    SELF(FishingState)->state_29     = 1;
    SELF(FishingState)->state_2A     = 1;

    record             = SELF(FishingState);
    record->counter_48 = 0;
    retired            = SELF(FishingState);
    record->origin_x   = 0xA2;
    record->origin_y   = 0xC2;
    retired->tint_5D   = 0;

    SELF(FishingState)->tint_5E    = 0;
    SELF(FishingState)->tint_5F    = 0;
    SELF(FishingState)->timer      = 0;
    SELF(FishingState)->step_index = 0;
    SELF(FishingState)->cue_index  = 0;

    tail             = SELF(FishingState);
    tail->pos_x      = 0;
    tail->step_delta = 4;
    tail->cue_index  = 0;
    Script_Select(0);

    tail            = SELF(FishingState);
    tail->sub_index = (tail->sub_index + 1);
}
