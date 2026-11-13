#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase and bumps
 * scratch state byte `0x03`. */
MATCH void func_801D6A2C(void) {
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
        record->origin_x_2E    = 0xF0;
        record->origin_y_30    = 0xBA;
        retired->step_timer_09 = 0;
    }

    FISHING_STATE->step_index_0A = 0;
    FISHING_STATE->cue_index_06  = 0;

    {
        FishingState* record;
        FishingState* retired;

        record            = FISHING_STATE;
        record->tint_5D   = 0;
        retired           = FISHING_STATE;
        record->pos_x_0C  = 0x6A;
        record->cursor_10 = 0x6A;
        retired->tint_5E  = 0;
    }

    FISHING_STATE->tint_5F = 0;
    FISHING_STATE->row_4B  = 0xFF;

    {
        FishingState* record;

        record               = FISHING_STATE;
        record->sub_index_03 = (record->sub_index_03 + 1);
    }
}
