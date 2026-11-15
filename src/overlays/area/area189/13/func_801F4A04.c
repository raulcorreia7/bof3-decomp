#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING s16 func_801F4A04(s32 x, s32 y) {
    s32   cell_x;
    s32   cell_y;
    u8    block;
    u32   packed;
    s8    c0;
    s8    c1;
    s8    c2;
    s8    c3;
    s32   height;
    Coord x_pos;
    Coord y_pos;

    x_pos.fixed = x + COORD_HALF;
    cell_x      = x_pos.part.integer;
    y_pos.fixed = y + COORD_HALF;
    cell_y      = y_pos.part.integer;
    block       = D_801F6138[(cell_y & 0xF0) | ((cell_x & 0xF0) >> 4)];
    packed      = MEM_PTR(u32, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)[((block & 0xF0) | (cell_y & 0xF)) * 0x60 + ((block & 0xF) << 4 | (cell_x & 0xF))];

    c0 = (s8)packed;
    c1 = (s8)(packed >> 8);
    c2 = (s8)(packed >> 16);
    c3 = (s8)(packed >> 24);

    if (x_pos.part.fraction + y_pos.part.fraction <= 0x10000) {
        height = c0 + (c1 - c0) * x_pos.part.fraction / 0x10000 + (c2 - c0) * y_pos.part.fraction / 0x10000;
    } else {
        height = c3 - (c3 - c2) * (0x10000 - x_pos.part.fraction) / 0x10000 - (c3 - c1) * (0x10000 - y_pos.part.fraction) / 0x10000;
    }
    return height << 5;
}
#else
INCLUDE_ASM(func_801F4A04);
#endif
