#include "area103_13.h"

MATCH void func_801F4F44(void) {
    func_801F5174(g_Task->timer, 0x80);
    func_801F53F0(g_Task->timer);
    g_Task->timer += 1;
    if (g_Task->timer >= 8U) {
        g_Task->header.step += 1;
    }
}
