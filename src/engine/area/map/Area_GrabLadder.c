#include "engine/game/00/game_00.h"

/* func_801B32A4 */
MATCH void Area_GrabLadder(void) {
    Area_ClimbStartGrab();
    TASK(Actor)->header.step = 2;
}
