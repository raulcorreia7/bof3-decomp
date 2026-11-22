#include "area030_04.h"

/* Integrates the AREA030 work record's two velocity pairs into its
 * position words and counts down the timer byte; when the timer reaches zero it
 * snaps both positions to the sign bit, clears the velocity words and raises the
 * work state. */
MATCH void func_801E0044(void) {
    FishingState* work;
    FishingState* checked;
    u8            timer;
    u8            state;
    /* FAKE: retail reuses v0 as the halfword accumulator. */
    FAKE_REG(u16, value, "v0");
    FishingState* ended;

    work                = FISHING_STATE;
    work->motion.unk_34 = work->motion.unk_34 + work->pos_x;
    timer               = work->step_timer;
    work->step_timer    = timer - 1;
    checked             = FISHING_STATE;
    work->y_38.pos_y    = work->y_38.pos_y + work->cursor_10;
    state               = 1;
    if (checked->step_timer == 0) {
        checked->handler_index = state;
        ended                  = FISHING_STATE;
        value                  = checked->motion.half.unk_34;
        value &= 0x8000;
        checked->motion.half.unk_34 = value;
        checked->pos_x              = 0;
        checked->cursor_10          = 0;
        value                       = checked->y_38.slot.low.pos_low;
        value &= 0x8000;
        checked->y_38.slot.low.pos_low = value;
        ended->mode_index              = 0;
    }
    Script_AnimStepLoop();
}
