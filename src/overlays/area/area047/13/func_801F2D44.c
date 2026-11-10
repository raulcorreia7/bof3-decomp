#include "area047_13.h"

MATCH void func_801F2D44(void) {
    s32 val;

    val = g_Task->vx;
    if (val > 0) {
        g_Task->vx = val - 1;
    }
    func_801F31F4((g_Task->vx << 19) >> 16);
    if ((u8)func_801F330C() == 0) {
        func_80196070();
    }
}
