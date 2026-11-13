#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Seeds the AREA030 panel scratch record for the cursor phase, arms
 * the mode helper with the cursor row and queues the cue that row selects. */
MATCH void func_801D339C(void) {
    FishingState* panel;
    FishingState* other;
    FishingState* state;
    u16           cue;

    Area_SelectSceneRecord(0x2B);

    panel               = FISHING_STATE;
    panel->origin_x_2E  = 0x186;
    panel->active_flags = 0x80;
    other               = FISHING_STATE;
    panel->origin_y_30  = 0x6E;
    other->counter_48   = 0;

    FISHING_STATE->state_29 = 2;
    FISHING_STATE->tint_5D  = 0;
    FISHING_STATE->tint_5E  = 0;
    FISHING_STATE->tint_5F  = 0;
    FISHING_STATE->state_2A = 0;

    Actor_SelectScript(FISHING_STATE->cue_index_06);

    cue = D_801E1DA0[FISHING_STATE->cue_index_06];
    if (cue != 0xFFFF) {
        SND_PlayCue(cue);
    }

    state                   = FISHING_STATE;
    state->handler_index_01 = (state->handler_index_01 + 1);
}
