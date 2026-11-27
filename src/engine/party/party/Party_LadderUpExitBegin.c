#include "engine/game/00/game_00.h"

/* func_801B7C58 */
/* Begins stepping off the ladder. */
MATCH void Party_LadderUpExitBegin(void) {
    if (Area_ClimbDismountExitBegin() & BYTE_MASK) {
        SELF(Actor)->unk_04++;
    }
}
