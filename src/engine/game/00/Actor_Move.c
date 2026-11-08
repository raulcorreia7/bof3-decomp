#include "game_00.h"

/* func_801C57B4 */
MATCH void Actor_Move(void) {
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    COORD_INT(g_Task->pos.z) += g_Task->vz;
}
