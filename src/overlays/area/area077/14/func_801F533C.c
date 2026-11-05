#include "area077_14.h"

MATCH void func_801F533C(void) {
    Actor* work;

    work                 = SP_REF(Actor*, 0x44);
    work->z.part.integer = 0x320;
    work->state_02 += 1;
    func_801F54B8();
}
