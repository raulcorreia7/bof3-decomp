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
        Area_SceneSelectRecord(*(u16*)(g_FishingSpecies + SELF(FishingState)->cue_index * 0x24));

        work        = SELF(FishingState);
        work->flags = (work->flags | ACTOR_FLAG_SEMI_TRANSPARENT);

        panel                          = SELF(FishingState);
        panel->state_2A                = D_801E2330[panel->counter_08][1];
        SELF(FishingState)->counter_48 = 2;

        Script_Select(D_801E2330[SELF(FishingState)->counter_08][0]);

        state                             = SELF(FishingState);
        state->bounce_speed               = -2;
        state->pos_x                      = 0;
        state->cursor_10                  = 0;
        state->timer                      = 0x10;
        SELF(FishingState)->handler_index = 1;
    }
}
