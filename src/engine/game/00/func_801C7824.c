#include "game_00.h"

MATCH s32 func_801C7824(s16 from_x, s16 from_y, s16 to_x, s16 to_y) {
    s16 step_x;
    s16 step_y;
    s16 dx;
    s16 dy;
    u16 x;
    u16 y;
    s8  total;
    u8  moved;
    u8  tries;

    for (tries = 0; tries < 2; tries++) {
        dx     = to_x - from_x;
        step_x = func_801C71AC(dx);
        dy     = to_y - from_y;
        step_y = func_801C71AC(dy);
        x      = from_x;
        y      = from_y;
        total  = func_801C7188(dx) + func_801C7188(dy);
        while (total >= 0) {
            moved = 0;
            if ((s16)x != to_x) {
                if (func_801C7608(x, y, x + step_x, y) & BYTE_MASK) {
                    x += step_x;
                    total--;
                    moved = 1;
                }
            }
            if ((s16)x == to_x && (s16)y == to_y) {
                return 1;
            }
            if ((s16)y != to_y) {
                if (func_801C7608(x, y, x, y + step_y) & BYTE_MASK) {
                    y += step_y;
                    total--;
                    moved = 1;
                }
            }
            if ((s16)x == to_x && (s16)y == to_y) {
                return 1;
            }
            if (!moved) {
                break;
            }
        }
        from_x ^= to_x;
        to_x ^= from_x;
        from_x ^= to_x;
        from_y ^= to_y;
        to_y ^= from_y;
        from_y ^= to_y;
    }
    return 0;
}
