#include "area077_14.h"

MATCH void func_801F4078(void) {
    /* FAKE: retail reserves 16 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 16);

    SELF(Actor)->pos.x.fixed = TO_COORD(116);
    SELF(Actor)->pos.y.fixed = TO_COORD(6);
    SELF(Actor)->pos.z.fixed = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) << 16;
    SELF(Actor)->vx          = 300;
    SELF(Actor)->header.mode++;
}
