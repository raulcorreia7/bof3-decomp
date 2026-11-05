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
    MATCH_FAKE_PIN(u16, value, "v0");
    FishingState* ended;

    work                    = FISHING_STATE;
    work->motion_34.unk_34  = work->motion_34.unk_34 + work->pos_x_0C;
    timer                   = work->step_timer_09;
    work->step_timer_09     = timer - 1;
    checked                 = FISHING_STATE;
    work->y_38.pos_y        = work->y_38.pos_y + work->cursor_10;
    state                   = 1;
    if (checked->step_timer_09 == 0) {
        checked->handler_index_01   = state;
        ended                       = FISHING_STATE;
        value                       = (u16)checked->motion_34.half.unk_34;
        value &= 0x8000;
        checked->motion_34.half.unk_34 = (s16)value;
        checked->pos_x_0C           = 0;
        checked->cursor_10          = 0;
        value                       = (u16)checked->y_38.half.low_38.pos_low_38;
        value &= 0x8000;
        checked->y_38.half.low_38.pos_low_38 = (s16)value;
        ended->mode_index_02        = 0;
    }
    func_8014D978();
}
