#include "game_00.h"

#define AREA_CELL_BLOCKED(x, y) ((s32 (*)(u16, u16))Area_CellIsBlocked)((u16)(x), (u16)(y))

#ifdef NON_MATCHING
NON_MATCHING s32 func_801A1C5C(s32 x, s32 y, s32 route, s32 unused) {
    /* FAKE: Register pins reproduce the retail saved-register assignment. */
    FAKE_REG(s32, sx, "s2");
    s32 sy;
    FAKE_REG(s32, sum, "s0");
    FAKE_REG(s32, part, "s5");
    s32 xhi;
    FAKE_REG(s32, yhi, "s3");
    u16  y_cell;
    char y_low;
    s32  xcell;
    s32  ycell;
    s32  cell;
    s16  y_low_word;
    sx = x;
    sy = y;
    switch (route & BYTE_MASK) {
        case FACING_UP:
            xhi   = sx >> 16;
            yhi   = ((u32)sy) >> 16;
            y_low = yhi;
            sum   = AREA_CELL_BLOCKED(xhi & HALF_MASK, y_low);
            part  = sum + AREA_CELL_BLOCKED((xhi + 1) & HALF_MASK, y_low);
            sum   = part;
            if (!(sx & HALF_MASK)) {
                sum = part + AREA_CELL_BLOCKED((xhi - 1) & HALF_MASK, y_low);
            }
            sum += (func_801A21EC(sx, sy) + func_801A21EC(sx + COORD_HALF, sy)) + func_801A21EC(sx - COORD_HALF, sy);
            break;

        case FACING_DOWN:
            if (sy & HALF_MASK) {
                xcell = sx >> 16;
                ycell = ((sy >> 16) + 1) & HALF_MASK;
                sum   = AREA_CELL_BLOCKED(xcell & HALF_MASK, ycell);
                part  = sum + AREA_CELL_BLOCKED((xcell + 1) & HALF_MASK, ycell);
                sum   = part;
                if (!(sx & HALF_MASK)) {
                    sum = part + AREA_CELL_BLOCKED((xcell - 1) & HALF_MASK, ycell);
                }
            } else {
                xhi    = sx >> 16;
                yhi    = ((u32)sy) >> 16;
                y_cell = yhi;
                sum    = AREA_CELL_BLOCKED(xhi & HALF_MASK, y_cell);
                part   = sum + AREA_CELL_BLOCKED((xhi + 1) & HALF_MASK, y_cell);
                sum    = part;
                if (!(sx & HALF_MASK)) {
                    sum = part + AREA_CELL_BLOCKED((xhi - 1) & HALF_MASK, y_cell);
                }
            }
            sum += (func_801A21EC(sx, sy) + func_801A21EC(sx + COORD_HALF, sy)) + func_801A21EC(sx - COORD_HALF, sy);
            break;

        case FACING_RIGHT:
            if (sx & HALF_MASK) {
                cell = ((sx >> 16) + 1) & HALF_MASK;
            } else {
                cell = ((u32)sx) >> 16;
            }
            /* cases 3 and 7 share the y-axis accumulation. */
            goto check_y;

        case FACING_LEFT:
            cell = ((u32)sx) >> 16;
        check_y:
            yhi = sy >> 16;

            sum        = AREA_CELL_BLOCKED(cell, yhi & HALF_MASK);
            y_low_word = yhi;
            part       = sum + AREA_CELL_BLOCKED(cell, (y_low_word + 1) & HALF_MASK);
            sum        = part;
            if (!(sy & HALF_MASK)) {
                sum = part + AREA_CELL_BLOCKED(cell, (y_low_word - 1) & HALF_MASK);
            }
            sum += (func_801A21EC(sx, sy) + func_801A21EC(sx, sy + COORD_HALF)) + func_801A21EC(sx, sy - COORD_HALF);
            break;

        default:
            sum = 1;
            break;
    }

    return (sum & BYTE_MASK) != 0;
}
#else
INCLUDE_ASM(func_801A1C5C);
#endif

#undef AREA_CELL_BLOCKED
