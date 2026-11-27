#include "area077_14.h"

MATCH void func_801F4078(void) {
    SELF(Actor)->pos.x.fixed = TO_COORD(116);
    SELF(Actor)->pos.y.fixed = TO_COORD(6);
    {
        Coord sample_x = {SELF(Actor)->pos.x.fixed};
        Coord sample_y = {SELF(Actor)->pos.y.fixed};

        SELF(Actor)->pos.z.fixed = Area_HeightSample(sample_x.fixed, sample_y.fixed) << 16;
    }
    SELF(Actor)->vx = 300;
    SELF(Actor)->header.mode++;
}
