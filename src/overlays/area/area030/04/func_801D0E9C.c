#include "area030_04.h"

/* Adds 8 to the work position and, once it reaches 0xF1, resets the
 * position to 0xF0, clears the sub-state bytes and steps the work state, then
 * submits the position. */
MATCH void func_801D0E9C(void) {
    FishingState* work;
    s32           position;
    FishingState* sub;

    work            = SELF(FishingState);
    position        = work->cursor_10 + 8;
    work->cursor_10 = position;
    if (position >= 241) {
        work->handler_index           = 1;
        sub                           = SELF(FishingState);
        work->cursor_10               = 0xF0;
        sub->mode_index               = 0;
        SELF(FishingState)->sub_index = 0;
    }
    Fishing_DrawHud(12, SELF(FishingState)->cursor_10);
}
