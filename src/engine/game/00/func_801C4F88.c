#include "game_00.h"

MATCH bool func_801C4F88(void) {
    if ((Actor_StepAnimOnce() & BYTE_MASK) != 0) {
        Script_Request(g_Task->direction == FACING_LEFT ? 0x3E : 0x3F);
        return true;
    }
    return false;
}
