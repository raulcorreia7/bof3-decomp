#include "engine/game/00/game_00.h"

/* func_801C4EC4 */
/* Turns the actor to the ladder over four animation requests, then flips its facing and returns true. */
MATCH bool Area_ClimbMountTurn(void) {
    u8 frames;

    SELF(Actor)->unk_0A = (SELF(Actor)->unk_0A - 1);
    frames              = SELF(Actor)->unk_0A;
    if (frames == 0) {
        Script_Request(SELF(Actor)->direction == FACING_RIGHT ? 0x37 : 0x34);
        SELF(Actor)->direction ^= 4;
        return true;
    }
    if (SELF(Actor)->direction == FACING_RIGHT) {
        Script_Request((7 - frames));
    } else {
        Script_Request((frames + 1));
    }
    SELF(Actor)->timer = 1;
    return false;
}
