#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase, then
 * arms the 0x0A subsystem step and retires scratch state byte `0x03`. */

/* Declared file-locally: this module's shared header omits the callee. */

MATCH void func_801D5B70(void) {
    Area_SelectSceneRecord(0x47);
    FISHING_STATE->active_flags = 0x80;
    FISHING_STATE->state_29     = 1;
    FISHING_STATE->state_2A     = 0;

    {
        FishingState* record;
        FishingState* retired;

        record                 = FISHING_STATE;
        record->counter_48     = 0;
        retired                = FISHING_STATE;
        record->origin_x_2E    = 0xE8;
        record->origin_y_30    = 0xC2;
        retired->step_timer_09 = 0;
    }

    FISHING_STATE->step_index_0A = 0;
    FISHING_STATE->tint_5D       = 0;
    FISHING_STATE->tint_5E       = 0;
    FISHING_STATE->tint_5F       = 0;

    Actor_SelectScript(0xA);

    {
        FishingState* record;

        record               = FISHING_STATE;
        record->sub_index_03 = (record->sub_index_03 - 1);
    }
}
