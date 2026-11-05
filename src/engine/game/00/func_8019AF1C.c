#include "game_00.h"

MATCH void func_8019AF1C(void) {
    Actor* work;
    s16    dist;

    dist = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    work = g_Task;
    if (dist >= COORD_INT(work->z) || (work->flags & ACTOR_FLAG_OFFSCREEN) || work->mode == 0) {
        work->vz      = D_801C8108[work->step][0];
        work->gravity = D_801C810C[work->step][0];
        work->mode++;
    }
    g_Task->x.fixed += g_Task->vx;
    g_Task->y.fixed += g_Task->vy;
    g_Task->z.fixed += g_Task->vz;
    g_Task->vz -= g_Task->gravity;
    func_8014D978();
    Area_SetDrawMode();
}
