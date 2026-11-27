#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Seeds the AREA030 panel scratch record for the cursor phase, arms
 * the mode helper with the cursor row and queues the cue that row selects. */
MATCH void func_801D339C(void) {
    FishingState* panel;
    FishingState* other;
    FishingState* state;
    u16           cue;

    Area_SceneSelectRecord(0x2B);

    panel               = SELF(FishingState);
    panel->origin_x     = 0x186;
    panel->active_flags = 0x80;
    other               = SELF(FishingState);
    panel->origin_y     = 0x6E;
    other->counter_48   = 0;

    SELF(FishingState)->state_29 = 2;
    SELF(FishingState)->tint_5D  = 0;
    SELF(FishingState)->tint_5E  = 0;
    SELF(FishingState)->tint_5F  = 0;
    SELF(FishingState)->state_2A = 0;

    Script_Select(SELF(FishingState)->cue_index);

    cue = D_801E1DA0[SELF(FishingState)->cue_index];
    if (cue != 0xFFFF) {
        SND_SEPlay(cue);
    }

    state                = SELF(FishingState);
    state->handler_index = (state->handler_index + 1);
}
