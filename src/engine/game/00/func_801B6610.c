#include "game_00.h"

MATCH s32 func_801B6610(s16 map_x, s16 map_y) {
    s32 value;
    s32 index;
    s32 sentinel;
    u8  entry;

    value    = Area_GetCellCode(map_x, map_y);
    index    = 0;
    sentinel = 0xFF;
    value &= BYTE_MASK;
    do {
        entry = s_AreaCellKinds[index];
        if (entry == sentinel)
            return 0;
        index += 1;
    } while (value != entry);
    return 1;
}
