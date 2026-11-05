#include "game_00.h"

MATCH s32 func_8019C244(void) {
    Actor* work;
    s32    x;
    s32    y;
    s32    hi;

    work = g_Task;
    x    = work->x.fixed;
    y    = work->y.fixed;
    switch (work->direction_08) {
        case 1:
            if ((((u32)y >> 0x0F) & 1) == 0) {
                hi = y >> 0x10;
                y &= HALF_MASK;
                hi -= 1;
                y |= hi << 0x10;
            }
            break;
        case 3:
            if ((((u32)x >> 0x0F) & 1) != 0) {
                hi = x >> 0x10;
                x &= HALF_MASK;
                hi += 1;
                x |= hi << 0x10;
            }
            break;
        case 5:
            if ((((u32)y >> 0x0F) & 1) != 0) {
                hi = y >> 0x10;
                y &= HALF_MASK;
                hi += 1;
                y |= hi << 0x10;
            }
            break;
        case 7:
            if ((((u32)x >> 0x0F) & 1) == 0) {
                hi = x >> 0x10;
                x &= HALF_MASK;
                hi -= 1;
                x |= hi << 0x10;
            }
            break;
    }
    return func_8019C344(x, y) & BYTE_MASK;
}
