#include "area189_13.h"

MATCH void func_801F54B0(void) {
    s32 ground;

    g_Task->timer = 8;
    g_Task->vx    = D_801F6308[g_Task->direction_08].x * 2;
    g_Task->vy    = D_801F6308[g_Task->direction_08].y * 2;
    ground        = func_801F4A04(g_Task->pos.x.fixed + g_Task->vx * g_Task->timer, g_Task->pos.y.fixed + g_Task->vy * g_Task->timer);
    g_Task->vz    = (TO_COORD(ground) - g_Task->pos.z.fixed) / g_Task->timer;
}
