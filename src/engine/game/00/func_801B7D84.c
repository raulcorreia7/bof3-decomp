#include "game_00.h"

MATCH void func_801B7D84(void) {
    if (Area_ClimbMountApproach() & BYTE_MASK) {
        TASK(Actor)->unk_04 = 2;
    }
}
