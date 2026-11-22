#include "area140_13.h"

MATCH void func_801F3320(void) {
    s32 i;

    i                             = COORD_INT(TASK(Actor)->pos.x);
    COORD_INT(TASK(Actor)->pos.x) = D_801F47F4[i].x;
    COORD_INT(TASK(Actor)->pos.y) = D_801F47F4[i].y;
    TASK(Actor)->direction        = D_801F47F4[i].facing;
    TASK(Actor)->param.unk_0B     = D_801F47F4[i].param;
    if (TASK(Actor)->direction == FACING_UP_LEFT) {
        COORD_INT(TASK(Actor)->pos.z) = 0;
        TASK(Actor)->header.step++;
    } else {
        COORD_INT(TASK(Actor)->pos.z) = 128;
        TASK(Actor)->header.step      = 4;
    }
    func_801F3950(TASK(Actor)->direction, COORD_INT(TASK(Actor)->pos.z));
}
