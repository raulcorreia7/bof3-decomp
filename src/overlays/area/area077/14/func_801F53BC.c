#include "area077_14.h"

MATCH void func_801F53BC(void) {
    Actor* work = g_Task;

    work->pos.y.fixed += 0x2000;
    COORD_INT(work->pos.z) += 16;
    if (work->pos.y.fixed == TO_COORD(53)) {
        work->header.step++;
    }
    func_801F54B8();
}
