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
    SELF(FishingState)->active_flags = 0x80;
    SELF(FishingState)->state_29     = 0;
    SELF(FishingState)->state_2A     = 0;

    record             = SELF(FishingState);
    record->counter_48 = 2;

    center           = SELF(FishingState);
    center->tint_5D  = 0;
    retired          = SELF(FishingState);
    center->unk_40   = 0x8000;
    center->unk_44   = 0x8000;
    retired->tint_5E = 0;

    SELF(FishingState)->tint_5F = 0;

    tail        = SELF(FishingState);
    tail->timer = 0x40;

    SELF(FishingState)->cue_index = 0;
    Script_Select(3);

    tail            = SELF(FishingState);
    tail->sub_index = (tail->sub_index + 1);
}
