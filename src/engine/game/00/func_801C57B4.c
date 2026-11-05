#include "game_00.h"

MATCH void func_801C57B4(void) {
    g_SpadWork->x.fixed += g_SpadWork->vx;
    g_SpadWork->y.fixed += g_SpadWork->vy;
    g_SpadWork->z.part.integer = (u16)(g_SpadWork->z.part.integer + g_SpadWork->vz);
}
