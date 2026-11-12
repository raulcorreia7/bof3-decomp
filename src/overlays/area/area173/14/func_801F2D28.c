#include "area173_14.h"

MATCH void func_801F2D28(void) {
    u8 mode;

    mode = g_Task->timer;
    func_801F3060(mode >> 3, (mode >> 2) & 0x1);
    g_Task->timer += 1;
    if (g_Task->timer >= 208U) {
        g_Task->header.step += 1;
    }
}
