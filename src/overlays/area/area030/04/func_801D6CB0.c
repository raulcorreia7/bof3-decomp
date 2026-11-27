#include "area030_04.h"

/* Advances the scratchpad step counter and moves the work position
 *           by the current entry's deltas, then redraws the panel row and
 *           two counters. */
MATCH void func_801D6CB0(void) {
    u8 steps;
    s8 direction;

    steps = SELF(FishingState)->timer;
    if (steps == 0) {
        if (D_801E207C[SELF(FishingState)->step_index].animation_id == -1) {
            SELF(FishingState)->step_index = D_801E207C[SELF(FishingState)->step_index].next_step;
        }
        Script_Request(D_801E207C[SELF(FishingState)->step_index].animation_id & 0x7F);
        SELF(FishingState)->timer      = D_801E207C[SELF(FishingState)->step_index].next_step;
        SELF(FishingState)->step_index = SELF(FishingState)->step_index + 1;
    } else {
        SELF(FishingState)->timer = steps - 1;
        if (!(D_801E207C[SELF(FishingState)->step_index - 1].animation_id & 0x80)) {
            Script_AnimStepLoop();
        }
    }
    SELF(FishingState)->pos_x += D_801E207C[SELF(FishingState)->step_index - 1].delta_x;
    SELF(FishingState)->cursor_10 += D_801E207C[SELF(FishingState)->step_index - 1].delta_y;
    SELF(FishingState)->cue_index -= D_801E207C[SELF(FishingState)->step_index - 1].delta_x;
    direction = 1;
    if (D_801E207C[SELF(FishingState)->step_index - 1].delta_y < 0) {
        /* FAKE: keeps GCC from turning the flag into sge (nor/srl); 7 pure-C spellings stayed at 96.24%. */
        FAKE_BARRIER();
        direction = 0;
    }
    func_801D6B28(direction);
    Fishing_DrawReelCursor(0xCE, 0x5C, 0x20, 0, 1, 0);
    Fishing_DrawFishArrow(227, 105, 0, 1);
}
