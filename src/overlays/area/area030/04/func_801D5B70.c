#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase, then
 * arms the 0x0A subsystem step and retires scratch state byte `0x03`. */

/* Declared file-locally: this module's shared header omits the callee. */

MATCH void func_801D5B70(void) {
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
        record->origin_x   = 0xE8;
        record->origin_y   = 0xC2;
        retired->timer     = 0;
    }

    SELF(FishingState)->step_index = 0;
    SELF(FishingState)->tint_5D    = 0;
    SELF(FishingState)->tint_5E    = 0;
    SELF(FishingState)->tint_5F    = 0;

    Script_Select(0xA);

    {
        FishingState* record;

        record            = SELF(FishingState);
        record->sub_index = (record->sub_index - 1);
    }
}
