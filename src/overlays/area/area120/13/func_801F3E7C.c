#include "area120_13.h"

MATCH void func_801F3E7C(void) {
    s32 x;
    s32 y;

    if ((MEM(s32, g_Task->vx) & 0xFFFF00) == 0x30600) {
        g_Task->timer       = 0;
        g_Task->header.step = 5;
        func_801F3DF0();
    } else {
        g_Task->timer += 8;
        x = abs(64 - g_Task->timer) + 0x40;
        y = abs(0x20 - (g_Task->timer >> 1)) + 0x20;
        if (g_Task->timer >= 128) {
            g_Task->timer       = 0;
            g_Task->header.step = 2;
        }
        func_801F3F5C(x, y, 1, 0);
    }
}
