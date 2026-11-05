#include "game_00.h"

MATCH void func_801C57B4(void) {
    g_Task->x.fixed += g_Task->vx;
    g_Task->y.fixed += g_Task->vy;
    COORD_INT(g_Task->z) += g_Task->vz;
}
