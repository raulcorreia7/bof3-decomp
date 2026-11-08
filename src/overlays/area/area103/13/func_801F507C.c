#include "area103_13.h"

MATCH void func_801F507C(void) {
    s32 delta;
    s32 steps;

    delta = 31 - g_Task->timer;
    steps = delta;
    if (delta < 0) {
        steps = delta + 3;
    }
    func_801F5174(steps >> 2, delta * 4);
    g_Task->timer += 1;
    if (g_Task->timer >= 25U) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}
