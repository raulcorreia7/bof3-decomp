#include "game_00.h"

MATCH void func_8019EA60(void) {
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    COORD_INT(TASK(Actor)->pos.z) += TASK(Actor)->vz;
    if ((TASK(Actor)->header.flags & ACTOR_FLAG_OFFSCREEN) != 0) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
