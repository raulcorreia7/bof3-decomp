#include "area030_04.h"

/* Advances the scratchpad step counter and moves the work position
 *           by the current entry's deltas, then redraws the panel row and
 *           two counters. */
MATCH void func_801D6CB0(void) {
    u8 steps;
    s8 direction;

    steps = FISHING_STATE->step_timer_09;
    if (steps == 0) {
        if (D_801E207C[FISHING_STATE->step_index_0A].anim_id == -1) {
            FISHING_STATE->step_index_0A = D_801E207C[FISHING_STATE->step_index_0A].next_step;
        }
        Actor_RequestScript(D_801E207C[FISHING_STATE->step_index_0A].anim_id & 0x7F);
        FISHING_STATE->step_timer_09 = D_801E207C[FISHING_STATE->step_index_0A].next_step;
        FISHING_STATE->step_index_0A = FISHING_STATE->step_index_0A + 1;
    } else {
        FISHING_STATE->step_timer_09 = steps - 1;
        if (!(D_801E207C[FISHING_STATE->step_index_0A - 1].anim_id & 0x80)) {
            Actor_StepAnimLoop();
        }
    }
    FISHING_STATE->pos_x_0C += D_801E207C[FISHING_STATE->step_index_0A - 1].delta_x;
    FISHING_STATE->cursor_10 += D_801E207C[FISHING_STATE->step_index_0A - 1].delta_y;
    FISHING_STATE->cue_index_06 -= D_801E207C[FISHING_STATE->step_index_0A - 1].delta_x;
    direction = 1;
    if (D_801E207C[FISHING_STATE->step_index_0A - 1].delta_y < 0) {
        /* FAKE: keeps GCC from turning the flag into sge (nor/srl); 7 pure-C spellings stayed at 96.24%. */
        FAKE_BARRIER();
        direction = 0;
    }
    func_801D6B28(direction);
    Fishing_DrawReelCursor(0xCE, 0x5C, 0x20, 0, 1, 0);
    Fishing_DrawFishArrow(227, 105, 0, 1);
}
