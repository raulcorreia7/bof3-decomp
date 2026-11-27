#include "engine/game/00/game_00.h"

/* func_801B35B0 */
/* Dismount phase 1: runs the rise and moves to phase 2 when it ends. */
MATCH void Area_ClimbDismountRiseStep(void) {
    if (Area_ClimbDismountRise() & BYTE_MASK) {
        SELF(Actor)->unk_03 = 2;
    }
}
