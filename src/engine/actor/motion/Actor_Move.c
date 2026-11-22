#include "engine/game/00/game_00.h"

/* func_801C57B4 */
MATCH void Actor_Move(void) {
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    COORD_INT(TASK(Actor)->pos.z) += TASK(Actor)->vz;
}
