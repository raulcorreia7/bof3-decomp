#include "area067_14.h"

MATCH void func_801F30EC(void) {
    AreaRippleQuad* quad;
    u8              timer;

    quad = (AreaRippleQuad*)&g_Task->vx;
    func_801F3AD8(quad);
    quad->height += 2;
    quad->y -= quad->height;
    func_801F3AD8(quad);
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (timer == 0) {
        g_Task->header.mode += 1;
    }
}
