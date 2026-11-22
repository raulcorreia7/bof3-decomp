#include "area067_14.h"

MATCH void func_801F30EC(void) {
    AreaRippleQuad* quad;
    u8              timer;

    quad = (AreaRippleQuad*)&TASK(Actor)->vx;
    func_801F3AD8(quad);
    quad->height += 2;
    quad->y -= quad->height;
    func_801F3AD8(quad);
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (timer == 0) {
        TASK(Actor)->header.mode += 1;
    }
}
