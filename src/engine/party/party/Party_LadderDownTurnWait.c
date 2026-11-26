#include "engine/game/00/game_00.h"

/* func_801B7DFC */
/* Waits after the turn. */
MATCH void Party_LadderDownTurnWait(void) {
    if (Area_ClimbMountTurnWait() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 4;
    }
}
