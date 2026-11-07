#include "game_00.h"

MATCH u8* func_801A0490(s32 map_x, s32 map_y, s32 table_index) {
    s32 x;
    s32 y;
    u8* entry;
    u8* cursor;

    entry  = g_EncounterZones[table_index & HALF_MASK];
    x      = map_x & BYTE_MASK;
    y      = map_y & BYTE_MASK;
    cursor = entry + 3;
loop_1:
    if (x < *entry) {
        goto advance; /* the entry does not cover the x coordinate */
    }
    if (y < cursor[-2]) {
        goto advance; /* the entry does not cover the y coordinate */
    }
    if (cursor[-1] < x) {
        goto advance; /* the entry ends before the x coordinate */
    }
    if (*cursor < y) {
    advance:
        cursor += 8;
        entry += 8;
        goto loop_1; /* try the next entry */
    }
    return entry;
}
