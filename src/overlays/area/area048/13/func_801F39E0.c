#include "area048_13.h"

MATCH void func_801F39E0(void) {
    func_801F3AE4(0x400, 0x858000 - (g_Task->timer << 12), 0x10);
    func_801F3AE4(0xC00, (g_Task->timer << 12) + 0x878000, 0x11);
    g_Task->timer += 1;
    if (g_Task->timer >= 17U) {
        g_Task->header.step += 1;
        g_Task->timer = 0;
    }
}
