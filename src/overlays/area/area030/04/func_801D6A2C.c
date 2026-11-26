#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase and bumps
 * scratch state byte `0x03`. */
MATCH void func_801D6A2C(void) {
    Area_SceneSelectRecord(0x47);
    SELF(FishingState)->active_flags = 0x80;
    SELF(FishingState)->state_29     = 1;
    SELF(FishingState)->state_2A     = 0;

    {
        FishingState* record;
        FishingState* retired;

        record             = SELF(FishingState);
        record->counter_48 = 0;
        retired            = SELF(FishingState);
        record->origin_x   = 0xF0;
        record->origin_y   = 0xBA;
        retired->timer     = 0;
    }

    SELF(FishingState)->step_index = 0;
    SELF(FishingState)->cue_index  = 0;

    {
        FishingState* record;
        FishingState* retired;

        record            = SELF(FishingState);
        record->tint_5D   = 0;
        retired           = SELF(FishingState);
        record->pos_x     = 0x6A;
        record->cursor_10 = 0x6A;
        retired->tint_5E  = 0;
    }

    SELF(FishingState)->tint_5F = 0;
    SELF(FishingState)->row_4B  = 0xFF;

    {
        FishingState* record;

        record            = SELF(FishingState);
        record->sub_index = (record->sub_index + 1);
    }
}
