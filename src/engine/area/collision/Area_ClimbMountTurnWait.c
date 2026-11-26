#include "engine/game/00/game_00.h"

/* func_801C4F88 */
/* Once the turn animation ends, requests script 0x3E facing left, 0x3F otherwise, and returns true. */
MATCH bool Area_ClimbMountTurnWait(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0) {
        Script_Request(TASK(Actor)->direction == FACING_LEFT ? 0x3E : 0x3F);
        return true;
    }
    return false;
}
