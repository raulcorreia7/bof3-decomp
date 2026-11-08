#include "area134_13.h"

MATCH void func_801F4388(void) {
    Actor* work;
    Actor* work2;
    s32    x;
    s32    y;
    s32    z;

    Area_ClearWorkColumn();
    work                   = g_Task;
    x                      = work->pos.x.fixed;
    y                      = work->pos.y.fixed;
    z                      = work->pos.z.fixed;
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
    SND_PlayCue(0x208);
}
