#include "area077_14.h"

MATCH void func_801F4078(void) {
    /* FAKE: retail reserves 16 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 16);

    TASK(Actor)->pos.x.fixed = TO_COORD(116);
    TASK(Actor)->pos.y.fixed = TO_COORD(6);
    TASK(Actor)->pos.z.fixed = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) << 16;
    TASK(Actor)->vx          = 300;
    TASK(Actor)->header.mode++;
}
