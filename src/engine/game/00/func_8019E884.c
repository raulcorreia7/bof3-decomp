#include "game_00.h"

MATCH void func_8019E884(void) {
    Actor* work;
    s32    add;
    s16    dist;

    add        = g_Task->vz + g_Task->gravity;
    g_Task->vz = add;
    COORD_INT(g_Task->pos.z) += add;
    Actor_StepAnimLoop();
    work = g_Task;
    dist = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    if (COORD_INT(work->pos.z) < dist) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}
