#include "area120_13.h"

MATCH void func_801F3D14(void) {
    u8 step;

    g_Task->timer += 2;
    step = g_Task->timer;
    func_801F3F5C(0x80 - (step * 2), 0x40 - step, 1, 0);
    if (g_Task->timer >= 0x40U) {
        Actor_Clear();
    }
}
