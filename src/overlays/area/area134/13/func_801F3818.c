/* The dispatch dance keeps every work-cell write. */
#define TASK_VOLATILE
#include "area134_13.h"

MATCH void func_801F3818(void) {
    Actor* work;

    work        = g_Task;
    g_Task      = &D_80146920;
    g_GameState = g_Game.members;
    g_Task      = work;
    TASK_SET(g_Game.members);
    g_Task = work;
    if (D_80146954 >= g_Game.members[0].pos.x.fixed) {
        work->header.mode = 0xD;
        g_Task->timer     = 0;
        return;
    }
    work->header.mode = 6;
}
