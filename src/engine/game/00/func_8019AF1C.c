#include "game_00.h"

MATCH void func_8019AF1C(void) {
    Actor* work;
    s16    dist;

    dist = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    work = g_Task;
    if (dist >= COORD_INT(work->pos.z) || (work->header.flags & ACTOR_FLAG_OFFSCREEN) || work->header.mode == 0) {
        work->vz      = D_801C8108[work->header.step][0];
        work->gravity = D_801C810C[work->header.step][0];
        work->header.mode++;
    }
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= g_Task->gravity;
    func_8014D978();
    Area_SetDrawMode();
}
