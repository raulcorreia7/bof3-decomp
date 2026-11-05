#include "game_00.h"

MATCH u8* func_801B3C3C(s32 bounds_x, s32 bounds_y) {
    s32 x;
    s32 y;
    u8* entry;
    u8* cursor;

    entry  = D_80181164[LOHU(g_GameAreaId)];
    x      = bounds_x & BYTE_MASK;
    y      = bounds_y & BYTE_MASK;
    cursor = entry + 3;
loop_1: /* scan each 8-byte bounds entry until one contains (x, y) */
    if (x < *entry) {
        goto block_5; /* outside this entry's range, try the next */
    }
    if (y < cursor[-2]) {
        goto block_5; /* the entry is not the wanted one */
    }
    if (cursor[-1] < x) {
        goto block_5; /* the entry is not the wanted one */
    }
    if (*cursor < y) {
        goto block_5; /* the entry is not the wanted one */
    }
    return entry;
block_5: /* advance both the entry pointer and the bounds cursor */
    cursor += 8;
    entry += 8;
    goto loop_1; /* the scan reached its end */
}
