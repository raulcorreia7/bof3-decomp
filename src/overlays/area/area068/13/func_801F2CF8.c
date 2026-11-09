#include "area068_13.h"

/* Point the mode record and the work cell at the first party record. */
MATCH void func_801F2CF8(void) {
    Actor* actor;

    actor       = g_Task;
    g_GameState = g_Game.members;
    TASK_SET(g_Game.members);
    if (D_80145EE8 == 0xC && D_80145EDA == 1) {
        Actor_SelectScript(0x6E);
        g_Task = actor;
        g_Game.members[0].unk_07 &= 0x11;
        actor->header.mode = 3;
    }
}
