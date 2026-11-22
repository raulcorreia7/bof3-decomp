#include "game_00.h"

MATCH bool func_801C4F88(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0) {
        Script_Request(TASK(Actor)->direction == FACING_LEFT ? 0x3E : 0x3F);
        return true;
    }
    return false;
}
