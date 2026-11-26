#include "game_00.h"

MATCH void func_801B7DC0(void) {
    if (Area_ClimbMountTurn() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 3;
    }
}
