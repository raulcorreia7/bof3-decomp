#include "area100_13.h"

MATCH void func_801F30B4(void) {
    Actor* work;
    s32    value;

    value             = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) << 16;
    work              = SELF(Actor);
    work->pos.z.fixed = value;
    work->vz          = 0;
    work->gravity     = 0;
    work->header.mode++;
}
