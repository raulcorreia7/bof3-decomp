#include "area173_14.h"

MATCH void func_801F38AC(void) {
    s16* slot;
    u8   x;
    u8   mode;

    slot       = &D_1F800038;
    x          = g_Task->timer;
    D_1F80003A = 0;
    *slot      = -(x * 4);
    func_801F3954(0);
    *slot = g_Task->timer * 4;
    func_801F3954(1);
    *slot      = 0;
    D_1F80003A = 0x180;
    func_801F3954(2);
    mode = g_Task->timer;
    if (mode != 0) {
        g_Task->timer = mode - 1;
    }
}
