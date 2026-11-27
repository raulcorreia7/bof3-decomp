#include "engine/game/00/game_00.h"

/* func_801B3400 */
/* Mount phase 3: waits out the turn animation and moves to phase 4. */
MATCH void Area_ClimbMountTurnWaitStep(void) {
    if (Area_ClimbMountTurnWait() & BYTE_MASK) {
        SELF(Actor)->unk_03 = 4;
    }
}
