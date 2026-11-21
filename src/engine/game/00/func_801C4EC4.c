#include "game_00.h"

MATCH bool func_801C4EC4(void) {
    u8 count;

    g_Task->unk_0A = (g_Task->unk_0A - 1);
    count          = g_Task->unk_0A;
    if (count == 0) {
        Script_Request(g_Task->direction == FACING_RIGHT ? 0x37 : 0x34);
        g_Task->direction ^= 4;
        return true;
    }
    if (g_Task->direction == FACING_RIGHT) {
        Script_Request((7 - count));
    } else {
        Script_Request((count + 1));
    }
    g_Task->timer = 1;
    return false;
}
