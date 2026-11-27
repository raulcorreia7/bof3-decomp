#include "area100_13.h"

MATCH s32 func_801F2CC0(void) {
    s32 value;

    SELF(Actor)->pos.x.fixed = TO_COORD(10);
    SELF(Actor)->pos.y.fixed = TO_COORD(99);
    value                    = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) << 16;
    SELF(Actor)->pos.z.fixed = value;
    SELF(Actor)->header.mode++;
}
