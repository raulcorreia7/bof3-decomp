#include "engine/game/00/game_00.h"

/* func_801B3388 */
/* Mount phase 1: runs the approach and moves to phase 2 when it ends. */
MATCH void Area_ClimbMountApproachStep(void) {
    if (Area_ClimbMountApproach() & BYTE_MASK) {
        SELF(Actor)->unk_03 = 2;
    }
}
