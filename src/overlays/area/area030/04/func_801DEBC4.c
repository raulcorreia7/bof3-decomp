#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* When the pending flag is set, clears the anchor flag, starts the
 * scene selected by the work row, latches the cursor height and direction and
 * arms the panel step. */
MATCH void func_801DEBC4(void) {
    FishingState* work;
    FishingState* panel;
    FishingState* state;

    if ((Script_AnimStepLoop() & BYTE_MASK) != 0) {
        D_801E3200 = 0;
        Area_SelectSceneRecord(*(u16*)(g_FishingSpecies + FISHING_STATE->cue_index * 0x24));

        work        = FISHING_STATE;
        work->flags = (work->flags | ACTOR_FLAG_SEMI_TRANSPARENT);

        panel                     = FISHING_STATE;
        panel->state_2A           = D_801E2331[panel->counter_08 * 2];
        FISHING_STATE->counter_48 = 2;

        Script_Select(D_801E2330[FISHING_STATE->counter_08 * 2]);

        state                        = FISHING_STATE;
        state->step_14               = -2;
        state->pos_x                 = 0;
        state->cursor_10             = 0;
        state->step_timer            = 0x10;
        FISHING_STATE->handler_index = 1;
    }
}
