#include "area168_13.h"

MATCH void func_801F2CE0(void) {
    Actor* actor;
    u8     i;
    s32    z;

    g_Task->unk_06     = 0;
    actor              = g_Task;
    actor->unk_18      = TO_COORD(16);
    actor->vx          = TO_COORD(16);
    actor->pos.z.fixed = 0;
    for (i = 0; i < 3; i++) {
        Actor* work   = g_Task;
        work->vy      = D_801F4B44[i].from;
        work->unk_1C  = D_801F4B44[i].to;
        z             = TO_COORD(COORD_INT(work->pos.z) + 128);
        work->gravity = z;
        work->vz      = z;
        func_801F2E10(&work->vx, &work->unk_18);
    }
    if (SYS_TestFlag(g_SceneEventFlags, 145) != 0) {
        g_Task->header.mode = 2;
    }
}
