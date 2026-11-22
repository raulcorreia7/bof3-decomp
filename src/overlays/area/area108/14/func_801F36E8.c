#include "area108_14.h"

MATCH void func_801F36E8(void) {
    Actor* work;

    TASK(Actor)->pos.x.fixed      = TO_COORD(36);
    TASK(Actor)->pos.y.fixed      = TO_COORD(65) + COORD_HALF;
    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(TASK(Actor)->pos.x.fixed, TO_COORD(65) + COORD_HALF);
    TASK(Actor)->unk_18           = 0;
    TASK(Actor)->tint.bytes.flags = 0x3D;
    TASK(Actor)->header.mode      = 1;
    work                          = TASK(Actor);
    work->tint.bytes.rgb.b        = 0;
    work->tint.bytes.rgb.g        = 0;
    work->tint.bytes.rgb.r        = 0;
}
