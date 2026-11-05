#include "game_00.h"

MATCH bool func_801C4EC4(void) {
    u8 count;

    g_Task->unk_0A = (u8)(g_Task->unk_0A - 1);
    count          = g_Task->unk_0A;
    if (count == 0) {
        Actor_RequestScript(g_Task->direction_08 == 3 ? 0x37 : 0x34);
        g_Task->direction_08 ^= 4;
        return true;
    }
    if (g_Task->direction_08 == 3) {
        Actor_RequestScript((u8)(7 - count));
    } else {
        Actor_RequestScript((u8)(count + 1));
    }
    g_Task->unk_09 = 1;
    return false;
}
