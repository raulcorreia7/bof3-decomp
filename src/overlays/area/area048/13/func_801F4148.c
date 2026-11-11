#include "area048_13.h"

MATCH void func_801F4148(void) {
    func_801F41F0(COORD_INT(g_Task->pos.x), D_801F4E74[g_Task->timer >> 1]);
    g_Task->timer++;
    if (g_Task->timer >= 7) {
        g_Task->timer       = 0;
        g_Task->header.step = 3;
    }
    func_801F4258(COORD_INT(g_Task->pos.x));
}
