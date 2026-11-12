#include "area030_04.h"

/* Subtracts 8 from the work position, clamps it to 0xAE when lower, increments the work state byte, and
 * submits the position. */
MATCH void func_801D0DDC(void) {
    FishingState* work;
    u8            state;
    s32           position;

    work            = FISHING_STATE;
    position        = work->cursor_10 - 8;
    work->cursor_10 = position;
    if (position < 174) {
        state                  = work->handler_index_01;
        work->cursor_10        = 0xAE;
        work->handler_index_01 = state + 1;
    }
    Fishing_DrawHud(12, FISHING_STATE->cursor_10);
}
