#include "game_00.h"

MATCH void func_801B7C58(void) {
    if (Area_ClimbDismountExitBegin() & BYTE_MASK) {
        TASK(Actor)->unk_04++;
    }
}
