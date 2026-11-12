#include "area077_14.h"

MATCH void func_801F5464(void) {
    Actor* work = g_Task;

    work->pos.y.fixed -= 0x2000;
    COORD_INT(work->pos.z) -= 16;
    if (work->pos.y.fixed == TO_COORD(52)) {
        work->header.step = 1;
    }
    func_801F54B8();
}
