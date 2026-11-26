#include "game_00.h"

MATCH void func_801B7DFC(void) {
    if (Area_ClimbMountTurnWait() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 4;
    }
}
