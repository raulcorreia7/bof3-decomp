#include "area077_14.h"

MATCH void func_801F5464(void) {
    Actor* work = g_Task;

    work->y.fixed -= 0x2000;
    work->z.part.integer -= 0x10;
    if (work->y.fixed == 0x340000) {
        work->step = 1;
    }
    func_801F54B8();
}
