#include "engine/game/00/game_00.h"

/* func_801AFD10 */
/* Steps a list window's scroll state and returns the first row to draw. */
MATCH s32 UI_ScrollList(u8* first_row, u8* scroll_y, u8* extra_rows, u8* scroll) {
    u8 state;
    u8 hi;
    u8 lo;
    u8 ret;

    state = *scroll;
    lo    = state & 0xF;
    hi    = state >> 4;
    if (hi == 1) {
        if (lo == 0) {
            *first_row = *first_row + 1;
        }
        lo = (lo + 4) % 12;
        if (lo == 0) {
            hi          = 0;
            *scroll_y   = 0;
            *extra_rows = 0;
            ret         = *first_row;
        } else {
            *scroll_y   = -lo;
            *extra_rows = 1;
            ret         = *first_row - 1;
        }
    } else if (hi == 0xF) {
        if (lo == 0) {
            *first_row = *first_row - 1;
            lo         = 8;
        } else {
            lo = lo - 4;
        }
        if (lo == 0) {
            hi          = 0;
            *scroll_y   = 0;
            *extra_rows = 0;
        } else {
            *scroll_y   = -lo;
            *extra_rows = 1;
        }
        ret = *first_row;
    } else {
        *scroll_y   = 0;
        *extra_rows = 0;
        ret         = *first_row;
    }
    *scroll = lo + (hi << 4);
    return ret;
}
