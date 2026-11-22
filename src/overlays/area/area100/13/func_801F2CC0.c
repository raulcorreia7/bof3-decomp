#include "area100_13.h"

MATCH s32 func_801F2CC0(void) {
    s32 value;

    TASK(Actor)->pos.x.fixed = TO_COORD(10);
    TASK(Actor)->pos.y.fixed = TO_COORD(99);
    value                    = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) << 16;
    TASK(Actor)->pos.z.fixed = value;
    TASK(Actor)->header.mode++;
}
