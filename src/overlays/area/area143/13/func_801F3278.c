#include "area143_13.h"

MATCH void func_801F3278(void) {
    s32 z;
    s32 height;
    s32 top;
    s32 bottom;

    z                   = g_Task->pos.z.fixed;
    height              = z + 8;
    g_Task->pos.z.fixed = height;
    if (height < 0x100) {
        top = height;
    } else {
        top = 0x100;
    }

    bottom = z - 0x18;
    if (bottom < 0) {
        bottom = 0;
    }

    func_801F3584(top, bottom, 1);

    if (bottom >= 0x100) {
        g_Task->pos.z.fixed = 0;
        g_Task->header.step++;
    }
}
