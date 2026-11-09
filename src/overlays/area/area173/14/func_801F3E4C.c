#include "area173_14.h"

MATCH void func_801F3E4C(void) {
    Actor* work;

    if (g_AreaSceneMode == 1) {
        g_AreaSceneMode = 0;
        g_Task->header.step++;
    }
    work = g_Task;
    if (abs(g_Game.members[0].pos.y.fixed - ((s32)COORD_INT(work->pos.y) << 16)) > TO_COORD(4) || abs(g_Game.members[0].pos.x.fixed - (((s32)COORD_INT(work->pos.x) + 1) << 16)) > TO_COORD(3)) {
        work->header.step++;
    }
}
