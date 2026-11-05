#include "game_00.h"

MATCH void func_8019EA60(void) {
    g_Task->x.fixed        = g_Task->x.fixed + g_Task->vx;
    g_Task->y.fixed        = g_Task->y.fixed + g_Task->vy;
    g_Task->z.part.integer = (g_Task->z.part.integer + g_Task->vz);
    if ((g_Task->flags & ACTOR_FLAG_OFFSCREEN) != 0) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
