#include "game_00.h"

MATCH u32 func_801C6FD4(s32 map_column, s32 map_row) {
    u16 row;
    s32 index;
    u16 tile;
    u16 offset;

    row = map_row & HALF_MASK;
    if (((u32)(map_column & HALF_MASK) >= (u8)D_80104000) || ((u32)row >= (u8)D_80104001)) {
        return 0;
    }
    index  = map_column + (D_80104000 * (s16)map_row);
    tile   = index;
    offset = tile >> 1;
    if ((tile & 1) != 0) {
        return MEM_PTR(u8, 0x80032000u)[offset] & 0xF;
    }
    return (MEM_PTR(u8, 0x80032000u)[offset] >> 4) & 0xF;
}
