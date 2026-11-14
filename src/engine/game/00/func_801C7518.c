#include "game_00.h"

MATCH s32 func_801C7518(s32 pos_x, s32 pos_y, s32 reach) {
    s32 off;
    s32 xa;
    s32 ya;
    u8  tile;
    u8  index;
    u16 px;
    u16 py;
    u16 fracy;

    xa    = pos_x + 0x8000;
    off   = ((reach & BYTE_MASK) + 1) << 0xF;
    off   = -off;
    xa    = off + xa;
    ya    = pos_y + 0x8000;
    ya    = off + ya;
    px    = xa;
    py    = ya;
    xa    = xa >> 0x10;
    ya    = ya >> 0x10;
    tile  = Area_GetWidth(xa, ya) & BYTE_MASK;
    index = ((reach << 2) | 0x1) & BYTE_MASK;
    if (tile < index) {
        return 0;
    }
    if (tile >= index + 4) {
        goto accept; /* a tile past the four neighbours is accepted */
    }
    if (px & HALF_MASK) {
        goto px_case; /* frac_x != 0 */
    }
    if (py & HALF_MASK) {
        goto py_case; /* frac_x == 0, frac_y != 0 */
    }
    if (tile != index) {
        return 0;
    }
accept:
    FAKE_BARRIER(); /* FAKE: keep the shared return-1 block distinct from px_case's. */
    return 1;
px_case:
    if (py & HALF_MASK) {
        return 0;
    }
    if (tile == index + 1) {
        goto accept; /* one column over */
    }
    if (tile != index + 3) {
        return 0;
    }
    FAKE_BARRIER(); /* FAKE: stop jump.c folding the px_case return into a setcc. */
    return 1;
py_case:
    if (tile == index + 2) {
        goto accept; /* one row down */
    }
    if (tile == index + 3) {
        goto accept; /* one row down, one column over */
    }
    return 0;
}
