#include "area112_13.h"

MATCH void func_801F2DA0(void) {
    Actor* work  = g_Task;
    u8     timer = work->unk_09 + 1;
    u16    y     = work->y.part.integer;

    work->unk_09 = timer;
    work->z.part.integer += y;
    if (g_Task->unk_09 >= 16) {
        g_Task->step++;
        func_801F2EA8();
    }
    func_801F3274();
}
