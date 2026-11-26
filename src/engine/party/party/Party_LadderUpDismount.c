#include "engine/game/00/game_00.h"

/* func_801B7C10 */
/* Runs the dismount rise of the up ladder. */
MATCH void Party_LadderUpDismount(void) {
    if (Area_ClimbDismountRise() & BYTE_MASK) {
        TASK(Actor)->unk_04++;
    }
}
