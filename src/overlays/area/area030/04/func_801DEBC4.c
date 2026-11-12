#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* When the pending flag is set, clears the anchor flag, starts the
 * scene selected by the work row, latches the cursor height and direction and
 * arms the panel step. */
MATCH void func_801DEBC4(void) {
    FishingState* work;
    FishingState* panel;
    FishingState* state;

    if ((Actor_StepAnimLoop() & BYTE_MASK) != 0) {
        D_801E3200 = 0;
        Area_SelectSceneRecord(*(u16*)(g_FishingSpecies + FISHING_STATE->cue_index_06 * 0x24));

        work        = FISHING_STATE;
        work->flags = (work->flags | ACTOR_FLAG_SEMI_TRANSPARENT);

        panel                     = FISHING_STATE;
        panel->state_2A           = D_801E2331[panel->counter_08 * 2];
        FISHING_STATE->counter_48 = 2;

        Actor_SelectScript(D_801E2330[FISHING_STATE->counter_08 * 2]);

        state                           = FISHING_STATE;
        state->step_14                  = -2;
        state->pos_x_0C                 = 0;
        state->cursor_10                = 0;
        state->step_timer_09            = 0x10;
        FISHING_STATE->handler_index_01 = 1;
    }
}
