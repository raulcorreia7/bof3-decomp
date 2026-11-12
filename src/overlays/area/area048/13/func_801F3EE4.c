#include "area048_13.h"

MATCH void func_801F3EE4(void) {
    func_801F41F0(COORD_INT(g_Task->pos.x), D_801F4E6C[g_Task->timer >> 1]);
    g_Task->timer++;
    if (g_Task->timer >= 5) {
        g_Task->timer = 0;
        g_Task->header.step++;
    }
    func_801F4258(COORD_INT(g_Task->pos.x));
}
