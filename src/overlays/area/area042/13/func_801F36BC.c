#include "area042_13.h"

MATCH void func_801F36BC(void) {
    Actor* work;

    func_801F37A8(SELF(Actor)->pos.z.fixed, 0x800000);
    work = SELF(Actor);
    work->pos.z.fixed += 4;
    if (work->pos.z.fixed >= -0xFF) {
        work->header.step++;
    }
}
