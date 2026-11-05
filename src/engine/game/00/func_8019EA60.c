#include "game_00.h"

MATCH void func_8019EA60(void) {
    g_SpadWork->x.fixed        = g_SpadWork->x.fixed + g_SpadWork->vx;
    g_SpadWork->y.fixed        = g_SpadWork->y.fixed + g_SpadWork->vy;
    g_SpadWork->z.part.integer = (u16)(g_SpadWork->z.part.integer + g_SpadWork->vz);
    if ((g_SpadWork->flags_00 & ACTOR_FLAG_OFFSCREEN) != 0) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
