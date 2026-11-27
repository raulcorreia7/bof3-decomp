#include "area145_14.h"

MATCH void func_801F38E0(void) {
    Actor* work;
    u8*    depth_target;
    s32    result;

    work                           = SELF(Actor);
    work->pos.x.fixed              = TO_COORD(10);
    work->pos.y.fixed              = TO_COORD(99);
    result                         = Area_HeightSample(work->pos.x.fixed, TO_COORD(99));
    depth_target                   = SELF(u8);
    FIELD(s32, depth_target, 0x3C) = result << 16;
    depth_target[1]++;
}
