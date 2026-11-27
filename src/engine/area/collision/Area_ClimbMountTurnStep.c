#include "engine/game/00/game_00.h"

/* func_801B33C4 */
/* Mount phase 2: runs the turn and moves to phase 3 when it ends. */
MATCH void Area_ClimbMountTurnStep(void) {
    if (Area_ClimbMountTurn() & BYTE_MASK) {
        SELF(Actor)->unk_03 = 3;
    }
}
