#include "game_00.h"

MATCH void func_801B7C10(void) {
    if (Area_ClimbDismountRise() & BYTE_MASK) {
        TASK(Actor)->unk_04++;
    }
}
