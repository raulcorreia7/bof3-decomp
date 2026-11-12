#include "game_00.h"

/* Route movement step table in main-exe data: one 8-byte record per route
 * {x step, y step}. */

MATCH s32 func_801A1BC0(Actor* record) {
    Actor* work;
    u8     route;
    s32    xstep;
    s32    ystep;
    s32    steps;
    s32    x;
    s32    y;
    s32    result;
    s32    next_x;
    s32    next_y;

    work   = g_Task;
    route  = work->direction_08 & 0x7;
    xstep  = g_FacingSteps[route].x;
    ystep  = g_FacingSteps[route].y;
    next_x = record->pos.x.fixed + xstep * (steps = work->state_70.byte + 1);
    x      = next_x;
    next_y = record->pos.y.fixed + ystep * steps;
    y      = next_y;

    if (work->state_70.byte == 0u) {
        result = func_801A1ED8(x, y, route, route);
    } else {
        result = func_801A1C5C(x, y, route, route);
    }
    return result & BYTE_MASK;
}
