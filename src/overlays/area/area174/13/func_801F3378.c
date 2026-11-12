#include "area174_13.h"

MATCH void func_801F3378(AreaShot* shot) {
    shot->active     = 1;
    shot->unk_04     = 0;
    shot->pos.x      = g_Task->pos.x;
    shot->pos.y      = g_Task->pos.y;
    shot->pos.z      = g_Task->pos.z;
    shot->velocity.x = (g_Task->vx - g_Task->pos.x.fixed) >> 5;
    shot->velocity.y = (g_Task->vy - g_Task->pos.y.fixed) >> 5;
    shot->velocity.z = (g_Task->vz - g_Task->pos.z.fixed) >> 5;
    shot->unk_08     = 0x40;
    shot->unk_0A     = 0x20;
    shot->timer      = 0x20;
    shot->angle      = func_801F3320(&g_Task->pos.x.fixed, &g_Task->vx);
}
