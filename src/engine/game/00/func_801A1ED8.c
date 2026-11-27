#include "game_00.h"

#define AREA_CELL_BLOCKED(x, y) ((u8 (*)(s32, s32))Area_CellIsBlocked)((x), (y))

/* Accumulates the blocked-cell probes around a 16.16 point for the route's facing. */
MATCH s32 func_801A1ED8(s32 x, s32 y, s32 route, s32 unused) {
    u8 sum;

    switch (route & BYTE_MASK) {
        case FACING_UP: {
            s32 col = x >> 16;
            s32 row = (y >> 16) & HALF_MASK;

            sum = AREA_CELL_BLOCKED(col & HALF_MASK, row);
            if (x & HALF_MASK) {
                sum += AREA_CELL_BLOCKED((col + 1) & HALF_MASK, row);
                sum += func_801A223C(x & ~HALF_MASK, y);
                sum += func_801A223C(x + COORD_HALF, y);
            }
            break;
        }
        case FACING_DOWN:
            if (y & HALF_MASK) {
                s32 col = x >> 16;
                s32 row = ((y >> 16) + 1) & HALF_MASK;

                sum = AREA_CELL_BLOCKED(col & HALF_MASK, row);
                if (x & HALF_MASK) {
                    sum += AREA_CELL_BLOCKED((col + 1) & HALF_MASK, row);
                    sum += func_801A223C(x & ~HALF_MASK, y);
                    sum += func_801A223C(x + COORD_HALF, y);
                }
            } else {
                s32 col = x >> 16;
                s32 row = (y >> 16) & HALF_MASK;

                sum = AREA_CELL_BLOCKED(col & HALF_MASK, row);
                if (x & HALF_MASK) {
                    sum += AREA_CELL_BLOCKED((col + 1) & HALF_MASK, row);
                    sum += func_801A223C(x & ~HALF_MASK, y);
                    sum += func_801A223C(x + COORD_HALF, y);
                }
            }
            break;
        case FACING_LEFT: {
            u16 column = x >> 16;
            s32 row    = y >> 16;

            sum = AREA_CELL_BLOCKED(column, row & HALF_MASK);
            if (y & HALF_MASK) {
                sum += AREA_CELL_BLOCKED(column, (row + 1) & HALF_MASK);
                sum += func_801A223C(x, y & ~HALF_MASK);
                sum += func_801A223C(x, y + COORD_HALF);
            }
            break;
        }
        case FACING_RIGHT:
            if (x & HALF_MASK) {
                u16 column = ((x >> 16) + 1) & HALF_MASK;
                s32 row    = y >> 16;

                sum = AREA_CELL_BLOCKED(column, row & HALF_MASK);
                if (y & HALF_MASK) {
                    sum += AREA_CELL_BLOCKED(column, (row + 1) & HALF_MASK);
                    sum += func_801A223C(x, y & ~HALF_MASK);
                    sum += func_801A223C(x, y + COORD_HALF);
                }
            } else {
                u16 column = x >> 16;
                s32 row    = y >> 16;

                sum = AREA_CELL_BLOCKED(column, row & HALF_MASK);
                if (y & HALF_MASK) {
                    sum += AREA_CELL_BLOCKED(column, (row + 1) & HALF_MASK);
                    sum += func_801A223C(x, y & ~HALF_MASK);
                    sum += func_801A223C(x, y + COORD_HALF);
                }
            }
            break;
        default:
            sum = 1;
            goto done;
    }
    sum += func_801A21EC(x, y);
done:
    return sum != 0;
}

#undef AREA_CELL_BLOCKED
