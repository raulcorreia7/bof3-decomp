#include "game_00.h"

MATCH void func_8019EA60(void) {
    g_Task->x.fixed += g_Task->vx;
    g_Task->y.fixed += g_Task->vy;
    COORD_INT(g_Task->z) += g_Task->vz;
    if ((g_Task->header.flags & ACTOR_FLAG_OFFSCREEN) != 0) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
