#include "game_00.h"

MATCH void func_8019AF1C(void) {
    Actor* work;
    s16    dist;

    dist = Area_SampleHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    work = g_SpadWork;
    if (dist >= work->z.part.integer || (work->flags_00 & ACTOR_FLAG_OFFSCREEN) || work->unk_01 == 0) {
        work->vz      = D_801C8108[work->state_02][0];
        work->gravity = D_801C810C[work->state_02][0];
        work->unk_01++;
    }
    g_SpadWork->x.fixed += g_SpadWork->vx;
    g_SpadWork->y.fixed += g_SpadWork->vy;
    g_SpadWork->z.fixed += g_SpadWork->vz;
    g_SpadWork->vz -= g_SpadWork->gravity;
    func_8014D978();
    Area_SetDrawMode();
}
