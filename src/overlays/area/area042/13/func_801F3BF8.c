#include "area042_13.h"

MATCH void func_801F3BF8(void) {
    Area_SetPosX(D_801F5350[(u8)(g_Task->timer / 3)]);
    g_Task->timer++;
    if (g_Task->timer >= 4) {
        g_Task->header.step = 1;
    }
}
