#include "area042_13.h"

MATCH void func_801F3A88(void) {
    Area_SetPosX(D_801F534C[g_Task->timer >> 1]);
    g_Task->timer += 1;
    if (g_Task->timer >= 5U) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}
