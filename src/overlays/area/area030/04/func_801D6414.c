#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Seeds the AREA030 scratch record for the later menu phase, aims the
 * panel window at the screen centre and bumps scratch state byte `0x03`. */
MATCH void func_801D6414(void) {
    FishingState* record;
    FishingState* center;
    FishingState* retired;
    FishingState* tail;

    Area_SceneSelectRecord(0x2B);
    TASK(FishingState)->active_flags = 0x80;
    TASK(FishingState)->state_29     = 0;
    TASK(FishingState)->state_2A     = 0;

    record             = TASK(FishingState);
    record->counter_48 = 2;

    center           = TASK(FishingState);
    center->tint_5D  = 0;
    retired          = TASK(FishingState);
    center->unk_40   = 0x8000;
    center->unk_44   = 0x8000;
    retired->tint_5E = 0;

    TASK(FishingState)->tint_5F = 0;

    tail        = TASK(FishingState);
    tail->timer = 0x40;

    TASK(FishingState)->cue_index = 0;
    Script_Select(3);

    tail            = TASK(FishingState);
    tail->sub_index = (tail->sub_index + 1);
}
