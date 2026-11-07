#include "area103_13.h"

MATCH void func_801F44B0(void) {
    if (g_Task->timer % 5 == 0) {
        func_801F4E70(g_Task->timer / 5 + 4);
    }
    g_Task->timer++;
    if (g_Task->timer / 5 == 3) {
        g_Task->header.step++;
        g_Task->timer = 1;
    }
}
