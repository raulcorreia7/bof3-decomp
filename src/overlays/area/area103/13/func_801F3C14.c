#include "area103_13.h"

MATCH void func_801F3C14(void) {
    Actor* work = SELF(Actor);

    work->timer               = 0;
    work->pos.x.fixed         = TO_COORD(87);
    work->pos.y.fixed         = TO_COORD(20);
    COORD_INT(work->pos.z)    = -0x100;
    work->unk_32              = 0;
    SELF(Actor)->param.unk_0B = 0;
    SELF(Actor)->header.step++;
}
