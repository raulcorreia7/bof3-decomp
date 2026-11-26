#include "engine/game/00/game_00.h"

/* func_801B343C */
/* Mount phase 4: lowers the actor onto the ladder; once it holds, the member climbs (step 2, phase 0). */
MATCH void Area_ClimbMountLowerStep(void) {
    if (Area_ClimbMountLower() & BYTE_MASK) {
        TASK(Actor)->header.step = 2;
        TASK(Actor)->unk_03      = 0;
    }
}
