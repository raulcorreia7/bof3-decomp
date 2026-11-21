#include "engine/game/00/game_00.h"

/* func_801B3C3C */
/* Returns the encounter zone entry of the current area that contains the cell. */
MATCH u8* Area_FindEncounterZone(s32 bounds_x, s32 bounds_y) {
    s32 x;
    s32 y;
    u8* entry;
    u8* cursor;

    entry  = g_EncounterZones[g_GameAreaId];
    x      = bounds_x & BYTE_MASK;
    y      = bounds_y & BYTE_MASK;
    cursor = entry + 3;
loop_1: /* scan each 8-byte bounds entry until one contains (x, y) */
    if (x < *entry) {
        goto block_5;
    }
    if (y < cursor[-2]) {
        goto block_5;
    }
    if (cursor[-1] < x) {
        goto block_5;
    }
    if (*cursor < y) {
        goto block_5;
    }
    return entry;
block_5: /* advance both the entry pointer and the bounds cursor */
    cursor += 8;
    entry += 8;
    goto loop_1;
}
