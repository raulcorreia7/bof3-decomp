#include "game_00.h"

MATCH void func_8019EA60(void) {
    SELF(Actor)->pos.x.fixed += SELF(Actor)->vx;
    SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
    COORD_INT(SELF(Actor)->pos.z) += SELF(Actor)->vz;
    if ((SELF(Actor)->header.flags & ACTOR_FLAG_OFFSCREEN) != 0) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
