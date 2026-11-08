#include "area042_13.h"

MATCH void func_801F3C88(void) {
    func_801F3D18(D_801F5354[g_Task->timer >> 1]);
    g_Task->timer++;
    if (g_Task->timer >= 7) {
        g_Task->timer       = 0;
        g_Task->header.step = 3;
    }
}
