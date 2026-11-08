#include "area068_13.h"

MATCH void func_801F2C6C(void) {
    Actor* temp_s0;

    temp_s0 = g_Task;
    if (D_80146865 != 0) {
        g_GameState = g_Game.members;
        TASK_SET(g_Game.members);
        g_Game.members[0].u.turn.command.target |= 0x40;
        Actor_SelectScript(0x6FU);
        g_Task = temp_s0;
        g_Game.members[0].unk_07 &= 0x11;
        temp_s0->header.mode = 2;
    }
}
