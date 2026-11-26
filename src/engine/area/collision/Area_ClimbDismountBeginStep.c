#include "engine/game/00/game_00.h"

/* func_801B3584 */
/* Dismount phase 0: begins the dismount and moves to phase 1. */
MATCH void Area_ClimbDismountBeginStep(void) {
    Area_ClimbDismountBegin();
    SELF(Actor)->unk_03 = 1;
}
