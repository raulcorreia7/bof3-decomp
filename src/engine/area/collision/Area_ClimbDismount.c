#include "engine/game/00/game_00.h"

/* func_801B3540 */
MATCH void Area_ClimbDismount(void) {
    Callback handler = g_AreaClimbDismountSteps[SELF(Actor)->unk_03];
    handler();
}
