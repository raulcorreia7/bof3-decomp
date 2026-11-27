#include "engine/game/00/game_00.h"

/* func_801C4D1C */
/* Requests the grab animation of the actor's facing: script 0x3C facing left, 0x3D otherwise. */
MATCH void Area_ClimbStartGrab(void) {
    u32 route;

    route = SELF(Actor)->direction;
    if (route == FACING_LEFT) {
        Script_Request(0x3C);
    } else {
        Script_Request(0x3D);
    }
}
