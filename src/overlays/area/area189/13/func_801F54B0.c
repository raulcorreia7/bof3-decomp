#include "area189_13.h"

MATCH void func_801F54B0(void) {
    s32 ground;

    TASK(Actor)->timer = 8;
    TASK(Actor)->vx    = D_801F6308[TASK(Actor)->direction].x * 2;
    TASK(Actor)->vy    = D_801F6308[TASK(Actor)->direction].y * 2;
    ground             = func_801F4A04(TASK(Actor)->pos.x.fixed + TASK(Actor)->vx * TASK(Actor)->timer, TASK(Actor)->pos.y.fixed + TASK(Actor)->vy * TASK(Actor)->timer);
    TASK(Actor)->vz    = (TO_COORD(ground) - TASK(Actor)->pos.z.fixed) / TASK(Actor)->timer;
}
