#include "engine/game/00/game_00.h"

/* func_801C57B4 */
MATCH void Actor_Move(void) {
    SELF(Actor)->pos.x.fixed += SELF(Actor)->vx;
    SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
    COORD_INT(SELF(Actor)->pos.z) += SELF(Actor)->vz;
}
