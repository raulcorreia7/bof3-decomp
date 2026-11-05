#include "game_00.h"

MATCH void func_8019E884(void) {
    Actor* work;
    s32    add;
    s16    dist;

    add        = g_Task->vz + g_Task->gravity;
    g_Task->vz = add;
    COORD_INT(g_Task->z) += add;
    func_8014D978();
    work = g_Task;
    dist = Area_SampleHeight(work->x.fixed, work->y.fixed);
    if (COORD_INT(work->z) < dist) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
