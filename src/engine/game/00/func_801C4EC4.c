#include "game_00.h"

MATCH bool func_801C4EC4(void) {
    u8 count;

    TASK(Actor)->unk_0A = (TASK(Actor)->unk_0A - 1);
    count               = TASK(Actor)->unk_0A;
    if (count == 0) {
        Script_Request(TASK(Actor)->direction == FACING_RIGHT ? 0x37 : 0x34);
        TASK(Actor)->direction ^= 4;
        return true;
    }
    if (TASK(Actor)->direction == FACING_RIGHT) {
        Script_Request((7 - count));
    } else {
        Script_Request((count + 1));
    }
    TASK(Actor)->timer = 1;
    return false;
}
