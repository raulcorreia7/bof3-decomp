#include "game_00.h"

MATCH void func_801B7E38(void) {
    if (Area_ClimbMountLower() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 5;
    }
}
