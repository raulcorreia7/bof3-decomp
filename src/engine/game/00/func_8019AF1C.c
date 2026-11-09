#include "game_00.h"

MATCH void func_8019AF1C(void) {
    Actor* work;
    s16    dist;

    dist = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    work = g_Task;
    if (dist >= COORD_INT(work->pos.z) || (work->header.flags & ACTOR_FLAG_OFFSCREEN) || work->header.mode == 0) {
        work->vz      = s_ActorTossArcs[work->header.step].vz;
        work->gravity = s_ActorTossArcs[work->header.step].gravity;
        work->header.mode++;
    }
    g_Task->pos.x.fixed += g_Task->vx;
    g_Task->pos.y.fixed += g_Task->vy;
    g_Task->pos.z.fixed += g_Task->vz;
    g_Task->vz -= g_Task->gravity;
    Actor_StepAnimLoop();
    Area_SetDrawMode();
}
