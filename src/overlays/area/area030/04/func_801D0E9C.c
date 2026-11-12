#include "area030_04.h"

/* Adds 8 to the work position and, once it reaches 0xF1, resets the
 * position to 0xF0, clears the sub-state bytes and steps the work state, then
 * submits the position. */
MATCH void func_801D0E9C(void) {
    FishingState* work;
    s32           position;
    FishingState* sub;

    work            = FISHING_STATE;
    position        = work->cursor_10 + 8;
    work->cursor_10 = position;
    if (position >= 241) {
        work->handler_index_01      = 1;
        sub                         = FISHING_STATE;
        work->cursor_10             = 0xF0;
        sub->mode_index_02          = 0;
        FISHING_STATE->sub_index_03 = 0;
    }
    Fishing_DrawHud(12, FISHING_STATE->cursor_10);
}
