#include "game_00.h"

MATCH bool func_801C4EC4(void) {
    u8 count;

    g_Task->unk_0A = (g_Task->unk_0A - 1);
    count          = g_Task->unk_0A;
    if (count == 0) {
        Actor_RequestScript(g_Task->direction_08 == FACING_E ? 0x37 : 0x34);
        g_Task->direction_08 ^= 4;
        return true;
    }
    if (g_Task->direction_08 == FACING_E) {
        Actor_RequestScript((7 - count));
    } else {
        Actor_RequestScript((count + 1));
    }
    g_Task->unk_09 = 1;
    return false;
}
