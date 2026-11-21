#include "area030_04.h"

/* Seeds the AREA030 scratch record for the later menu phase, clears
 * its panel state and bumps scratch state byte `0x03`. */
MATCH void func_801D5A48(void) {
    FishingState* record;
    FishingState* retired;
    FishingState* tail;

    Area_SelectSceneRecord(0x21);
    FISHING_STATE->active_flags = 0x80;
    FISHING_STATE->state_29     = 1;
    FISHING_STATE->state_2A     = 1;

    record             = FISHING_STATE;
    record->counter_48 = 0;
    retired            = FISHING_STATE;
    record->origin_x   = 0xA2;
    record->origin_y   = 0xC2;
    retired->tint_5D   = 0;

    FISHING_STATE->tint_5E    = 0;
    FISHING_STATE->tint_5F    = 0;
    FISHING_STATE->step_timer = 0;
    FISHING_STATE->step_index = 0;
    FISHING_STATE->cue_index  = 0;

    tail             = FISHING_STATE;
    tail->pos_x      = 0;
    tail->step_delta = 4;
    tail->cue_index  = 0;
    Script_Select(0);

    tail            = FISHING_STATE;
    tail->sub_index = (tail->sub_index + 1);
}
