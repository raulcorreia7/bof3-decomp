#include "engine/game/00/game_00.h"

/* func_801B7DC0 */
/* Turns the actor to the ladder. */
MATCH void Party_LadderDownTurn(void) {
    if (Area_ClimbMountTurn() & BYTE_MASK) {
        SELF(Actor)->unk_04 = 3;
    }
}
