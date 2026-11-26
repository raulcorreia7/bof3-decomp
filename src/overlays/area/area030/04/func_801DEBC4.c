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
        Area_SceneSelectRecord(*(u16*)(g_FishingSpecies + TASK(FishingState)->cue_index * 0x24));

        work        = TASK(FishingState);
        work->flags = (work->flags | ACTOR_FLAG_SEMI_TRANSPARENT);

        panel                          = TASK(FishingState);
        panel->state_2A                = D_801E2330[panel->counter_08][1];
        TASK(FishingState)->counter_48 = 2;

        Script_Select(D_801E2330[TASK(FishingState)->counter_08][0]);

        state                             = TASK(FishingState);
        state->bounce_speed               = -2;
        state->pos_x                      = 0;
        state->cursor_10                  = 0;
        state->timer                      = 0x10;
        TASK(FishingState)->handler_index = 1;
    }
}
