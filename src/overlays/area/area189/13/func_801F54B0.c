#include "area189_13.h"

MATCH void func_801F54B0(void) {
    s32 ground;

    SELF(Actor)->timer = 8;
    SELF(Actor)->vx    = D_801F6308[SELF(Actor)->direction].x * 2;
    SELF(Actor)->vy    = D_801F6308[SELF(Actor)->direction].y * 2;
    ground             = func_801F4A04(SELF(Actor)->pos.x.fixed + SELF(Actor)->vx * SELF(Actor)->timer, SELF(Actor)->pos.y.fixed + SELF(Actor)->vy * SELF(Actor)->timer);
    SELF(Actor)->vz    = (TO_COORD(ground) - SELF(Actor)->pos.z.fixed) / SELF(Actor)->timer;
}
