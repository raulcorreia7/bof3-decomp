#include "area077_14.h"

MATCH void func_801F533C(void) {
    Actor* work;

    work               = SP_REF(Actor*, 0x44);
    COORD_INT(work->z) = 0x320;
    work->step += 1;
    func_801F54B8();
}
