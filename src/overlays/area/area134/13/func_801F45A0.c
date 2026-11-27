#include "area134_13.h"

MATCH void func_801F45A0(void) {
    Actor* work;
    s32    sample_y;

    work     = SELF(Actor);
    work->vx = work->pos.x.fixed + TO_COORD(-1);
    sample_y = work->pos.y.fixed + TO_COORD(-1);
    work->vy = sample_y;
    {
        Coord x = {work->vx};
        Coord y = {sample_y};

        work->vz = Area_HeightSample(x.fixed, y.fixed) << 0x10;
    }
    work->unk_1C       = 0;
    SELF(Actor)->timer = 10;
    SELF(Actor)->header.mode += 1;
}
