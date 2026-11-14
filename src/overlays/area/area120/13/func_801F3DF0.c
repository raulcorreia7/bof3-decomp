#include "area120_13.h"

MATCH void func_801F3DF0(void) {
    /* FAKE: pin registers to match retail allocation; pure C picks different registers. */
    FAKE_REG(Actor*, t, "a1");
    FAKE_REG(u32, timer, "v1");
    FAKE_REG(s32, a, "a0");
    s32 v;

    g_Task->timer++;
    t     = g_Task;
    timer = t->timer;
    a     = 8;
    v     = a - timer;
    if (v < 0) {
        v = -v;
    }
    a = a - v;
    if (timer >= 0x10) {
        t->timer            = 0;
        g_Task->header.step = 2;
    }
    func_801F3F5C(0x80, 0x40, 1, -a << 4);
}
