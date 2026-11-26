#include "engine/game/00/game_00.h"

/* func_801B7E38 */
/* Lowers the actor onto the ladder. */
MATCH void Party_LadderDownLower(void) {
    if (Area_ClimbMountLower() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 5;
    }
}
