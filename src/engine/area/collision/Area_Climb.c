#include "engine/game/00/game_00.h"

/* func_801B3260 */
MATCH void Area_Climb(void) {
    Callback handler = g_AreaClimbSteps[SELF(Actor)->header.step];
    handler();
}
