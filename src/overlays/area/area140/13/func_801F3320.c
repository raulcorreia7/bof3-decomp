#include "area140_13.h"

MATCH void func_801F3320(void) {
    s32 i;

    i                             = COORD_INT(SELF(Actor)->pos.x);
    COORD_INT(SELF(Actor)->pos.x) = D_801F47F4[i].x;
    COORD_INT(SELF(Actor)->pos.y) = D_801F47F4[i].y;
    SELF(Actor)->direction        = D_801F47F4[i].facing;
    SELF(Actor)->param.unk_0B     = D_801F47F4[i].param;
    if (SELF(Actor)->direction == FACING_UP_LEFT) {
        COORD_INT(SELF(Actor)->pos.z) = 0;
        SELF(Actor)->header.step++;
    } else {
        COORD_INT(SELF(Actor)->pos.z) = 128;
        SELF(Actor)->header.step      = 4;
    }
    func_801F3950(SELF(Actor)->direction, COORD_INT(SELF(Actor)->pos.z));
}
