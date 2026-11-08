#include "area132_13.h"

MATCH void func_801F30C0(void) {
    Actor* work = g_Task;
    Actor* work2;
    s32    x = work->pos.x.fixed;
    s32    y = work->pos.y.fixed;
    s32    z = work->pos.z.fixed;

    work->timer            = 64;
    work2                  = g_Task;
    /* FAKE: indexed stores across gravity and active_flags preserve the coordinate load order. */
    MEM_PTR(s16, work)[16] = 0;
    MEM_PTR(s32, work)[9]  = 0x1000000;
    work->vx               = x;
    work->vy               = y;
    work->vz               = z;
    work->unk_1C           = z;
    work2->header.mode++;
    SND_PlayCue(0x207);
}
