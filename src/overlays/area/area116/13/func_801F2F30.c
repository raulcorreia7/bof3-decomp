#include "area116_13.h"

MATCH void func_801F2F30(void) {
    Actor* work;
    s32    pos[3];

    work   = SP_REF(Actor*, 0x44);
    pos[0] = work->x.fixed;
    pos[1] = work->y.fixed;
    pos[2] = work->z.fixed;
    func_801F2F78(pos);
}
