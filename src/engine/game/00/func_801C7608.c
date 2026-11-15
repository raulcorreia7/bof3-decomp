#include "game_00.h"

MATCH bool func_801C7608(s16 x0, s16 y0, s16 x1, s16 y1) {
    s16 tmp;
    s16 dx;
    s16 dy;
    s32 prod;
    s32 blocked;
    u32 probe_a;
    u32 probe_b;
    u32 class_a;
    u32 cls;

    if (x0 == x1 && y0 == y1) {
        return 1;
    }
    if (x0 > x1 || (x0 == x1 && y0 > y1)) {
        tmp = x0;
        x0  = x1;
        x1  = tmp;
        tmp = y0;
        y0  = y1;
        /* FAKE: the order lock steers regalloc */
        FAKE_ORDER_LOCK_BEGIN
            y1 = tmp;
        FAKE_ORDER_LOCK_END;
    }
    if (x0 != x1) {
        if (y0 == y1) {
            cls = Area_GetWidth(x0, y0) & BYTE_MASK;
            if (cls >= 2 && cls != 3) {
                return 1;
            }
            return 0;
        }
    }
    if (x0 == x1) {
        if (y0 != y1) {
            return (Area_GetWidth(x0, y0) & BYTE_MASK) >= 3;
        }
    }
    dx   = x1 - x0;
    dy   = y1 - y0;
    prod = dx * dy;
    if (prod > 0) {
        blocked = (Area_GetWidth(x0, y0) & BYTE_MASK) < 5;
    } else {
        probe_a = Area_GetWidth(x0, y0);
        probe_b = Area_GetWidth(x0, y1) & BYTE_MASK;
        if (probe_b >= 4) {
            /* kept: shares the return-1 exit; plain returns score 94.07% */
            goto pass;
        }
        class_a = probe_a & BYTE_MASK;
        if (class_a < 2) {
            return 0;
        }
        if (class_a == 3) {
            return 0;
        }
        blocked = (Area_GetWidth(x0, y1) & BYTE_MASK) < 3;
    }
    if (!blocked) {
    pass:
        return 1;
    }
    return 0;
}
