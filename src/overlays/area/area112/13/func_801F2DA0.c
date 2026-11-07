#include "area112_13.h"

MATCH void func_801F2DA0(void) {
    Actor* work  = g_Task;
    u8     timer = work->timer + 1;
    u16    y     = COORD_INT(work->pos.y);

    work->timer = timer;
    COORD_INT(work->pos.z) += y;
    if (g_Task->timer >= 16) {
        g_Task->header.step++;
        func_801F2EA8();
    }
    func_801F3274();
}
