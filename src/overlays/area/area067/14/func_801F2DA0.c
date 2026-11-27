#include "area067_14.h"

/* Raises the ripple's vertical span, grows its radius and counts the step down. */
MATCH void func_801F2DA0(void) {
    AreaRippleQuad* quad;
    u8              count;

    quad = (AreaRippleQuad*)&SELF(Actor)->vx;
    if (SELF(Actor)->timer >= 0x1A) {
        quad->radius += 2;
    } else {
        quad->radius -= 2;
    }
    quad->height += 0x40;
    func_801F31C8(quad);
    ACTOR_COUNT_DOWN(SELF(Actor), count, timer);
    if (count == 0) {
        SELF(Actor)->header.mode++;
    }
}
