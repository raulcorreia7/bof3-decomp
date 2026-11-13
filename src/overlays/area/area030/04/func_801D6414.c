#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Seeds the AREA030 scratch record for the later menu phase, aims the
 * panel window at the screen centre and bumps scratch state byte `0x03`. */
MATCH void func_801D6414(void) {
    FishingState* record;
    FishingState* center;
    FishingState* retired;
    FishingState* tail;

    Area_SelectSceneRecord(0x2B);
    FISHING_STATE->active_flags = 0x80;
    FISHING_STATE->state_29     = 0;
    FISHING_STATE->state_2A     = 0;

    record             = FISHING_STATE;
    record->counter_48 = 2;

    center           = FISHING_STATE;
    center->tint_5D  = 0;
    retired          = FISHING_STATE;
    center->unk_40   = 0x8000;
    center->unk_44   = 0x8000;
    retired->tint_5E = 0;

    FISHING_STATE->tint_5F = 0;

    tail                = FISHING_STATE;
    tail->step_timer_09 = 0x40;

    FISHING_STATE->cue_index_06 = 0;
    Actor_SelectScript(3);

    tail               = FISHING_STATE;
    tail->sub_index_03 = (tail->sub_index_03 + 1);
}
