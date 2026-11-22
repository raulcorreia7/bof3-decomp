#include "game_00.h"

#define AREA_CELL_BLOCKED(x, y) ((s32 (*)(u16, u16))Area_CellIsBlocked)((u16)(x), (u16)(y))

/* Accumulates the blocked-cell probes around a 16.16 point for the route's facing. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801A1ED8(s32 x, s32 y, s32 route, s32 unused) {
    s32 sum;
    s32 xcell;
    s32 ycell;

    switch (route & BYTE_MASK) {
        case FACING_UP:
            xcell = x >> 16;
            ycell = ((u32)y) >> 16;
            sum   = AREA_CELL_BLOCKED(xcell & HALF_MASK, ycell);
            if (x & HALF_MASK) {
                sum += AREA_CELL_BLOCKED((xcell + 1) & HALF_MASK, ycell);
                sum += func_801A223C(x & ~HALF_MASK, y);
                sum += func_801A223C(x + COORD_HALF, y);
            }
            break;

        case FACING_DOWN:
            if (y & HALF_MASK) {
                xcell = x >> 16;
                ycell = ((y >> 16) + 1) & HALF_MASK;
                sum   = AREA_CELL_BLOCKED(xcell & HALF_MASK, ycell);
                if (x & HALF_MASK) {
                    sum += AREA_CELL_BLOCKED((xcell + 1) & HALF_MASK, ycell);
                    sum += func_801A223C(x & ~HALF_MASK, y);
                    sum += func_801A223C(x + COORD_HALF, y);
                }
            } else {
                xcell = x >> 16;
                ycell = ((u32)y) >> 16;
                sum   = AREA_CELL_BLOCKED(xcell & HALF_MASK, ycell);
                if (x & HALF_MASK) {
                    sum += AREA_CELL_BLOCKED((xcell + 1) & HALF_MASK, ycell);
                    sum += func_801A223C(x & ~HALF_MASK, y);
                    sum += func_801A223C(x + COORD_HALF, y);
                }
            }
            break;

        case FACING_RIGHT:
            if (x & HALF_MASK) {
                xcell = ((x >> 16) + 1) & HALF_MASK;
            } else {
                xcell = ((u32)x) >> 16;
            }
            goto probe_x;

        case FACING_LEFT:
            xcell = ((u32)x) >> 16;
        probe_x:
            ycell = y >> 16;
            sum   = AREA_CELL_BLOCKED(xcell, ycell & HALF_MASK);
            if (y & HALF_MASK) {
                sum += AREA_CELL_BLOCKED(xcell, (ycell + 1) & HALF_MASK);
                sum += func_801A223C(x, y & ~HALF_MASK);
                sum += func_801A223C(x, y + COORD_HALF);
            }
            break;

        default:
            return 1;
    }

    sum += func_801A21EC(x, y);
    return (sum & BYTE_MASK) != 0;
}
#else
INCLUDE_ASM(func_801A1ED8);
#endif

#undef AREA_CELL_BLOCKED
