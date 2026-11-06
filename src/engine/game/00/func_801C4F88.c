#include "game_00.h"

MATCH bool func_801C4F88(void) {
    if ((func_8014DAEC() & 0xFF) != 0) {
        Actor_RequestScript(g_Task->direction_08 == 7 ? 0x3E : 0x3F);
        return true;
    }
    return false;
}
