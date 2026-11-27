#include "area108_14.h"

MATCH void func_801F36E8(void) {
    Actor* work;

    SELF(Actor)->pos.x.fixed      = TO_COORD(36);
    SELF(Actor)->pos.y.fixed      = TO_COORD(65) + COORD_HALF;
    COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(SELF(Actor)->pos.x.fixed, TO_COORD(65) + COORD_HALF);
    SELF(Actor)->unk_18           = 0;
    SELF(Actor)->tint.bytes.flags = 0x3D;
    SELF(Actor)->header.mode      = 1;
    work                          = SELF(Actor);
    work->tint.bytes.rgb.b        = 0;
    work->tint.bytes.rgb.g        = 0;
    work->tint.bytes.rgb.r        = 0;
}
