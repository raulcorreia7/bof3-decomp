#include "area068_13.h"

MATCH void func_801F2C6C(void) {
    Actor* task;

    task = g_Task;
    if (D_80146865 != 0) {
        g_GameState = g_Game.members;
        TASK_SET(g_Game.members);
        g_Game.members[0].u.turn.command.target |= 0x40;
        Actor_SelectScript(0x6FU);
        g_Task = task;
        g_Game.members[0].unk_07 &= 0x11;
        task->header.mode = 2;
    }
}
