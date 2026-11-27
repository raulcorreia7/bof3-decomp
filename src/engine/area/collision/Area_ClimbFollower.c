#include "engine/game/00/game_00.h"

/* func_801BD7F8 */
/* Runs the follower's ladder step that header.step selects. */
MATCH void Area_ClimbFollower(void) {
    g_AreaClimbFollowerSteps[SELF(Actor)->header.step]();
}
