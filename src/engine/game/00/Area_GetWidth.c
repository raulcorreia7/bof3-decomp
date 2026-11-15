#include "game_00.h"

/* func_801C6FD4 */
MATCH u32 Area_GetWidth(s32 map_column, s32 map_row) {
    u16 row;
    s32 index;
    u16 tile;
    u16 offset;

    row = map_row & HALF_MASK;
    if (((u32)(map_column & HALF_MASK) >= g_AreaMapBundle.width) || (row >= g_AreaMapBundle.height)) {
        return 0;
    }
    index  = map_column + (g_AreaMapBundle.width * (s16)map_row);
    tile   = index;
    offset = tile >> 1;
    if ((tile & 0x1) != 0) {
        return MEM_PTR(u8, 0x80032000u)[offset] & 0xF;
    }
    return (MEM_PTR(u8, 0x80032000u)[offset] >> 4) & 0xF;
}
