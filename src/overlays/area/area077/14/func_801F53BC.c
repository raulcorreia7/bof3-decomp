#include "area077_14.h"

MATCH void func_801F53BC(void) {
    Actor* work = g_Task;

    work->y.fixed += 0x2000;
    COORD_INT(work->z) += 0x10;
    if (work->y.fixed == 0x350000) {
        work->header.step++;
    }
    func_801F54B8();
}
