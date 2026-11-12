#include "area048_13.h"

MATCH void func_801F3874(void) {
    u8 timer;

    timer = g_Task->timer;
    func_801F3AE4(timer << 4, 0x858000, (timer >= 49U) << 4);
    timer = g_Task->timer;
    func_801F3AE4((timer + 128) << 4, 0x878000, timer >= 49U ? 0x11 : 1);
    g_Task->timer += 1;
    if (g_Task->timer >= 65U) {
        g_Task->header.step += 1;
        g_Task->timer = 0;
    }
}
