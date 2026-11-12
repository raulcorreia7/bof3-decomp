/* The dispatch dance keeps every work-cell write. */
#define TASK_VOLATILE
#include "area134_13.h"

MATCH void func_801F2F90(void) {
    Actor* work;

    work        = g_Task;
    g_Task      = g_Actors;
    g_GameState = g_Game.members;
    g_Task      = work;
    TASK_SET(g_Game.members);
    g_Task = work;
    if (FIELD(s32, D_801468BC, 0x0) >= g_Game.members[0].pos.x.fixed) {
        work->header.mode = 0xD;
        g_Task->timer     = 0;
        return;
    }
    work->header.mode = 8;
}
