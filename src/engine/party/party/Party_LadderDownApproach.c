#include "engine/game/00/game_00.h"

/* func_801B7D84 */
/* Walks the actor to the ladder top. */
MATCH void Party_LadderDownApproach(void) {
    if (Area_ClimbMountApproach() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 2;
    }
}
