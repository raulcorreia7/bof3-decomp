#include "area132_13.h"

MATCH void func_801F30C0(void) {
    Actor* work = g_Task;
    Actor* work2;
    s32    x = work->pos.x.fixed;
    s32    y = work->pos.y.fixed;
    s32    z = work->pos.z.fixed;

    work->timer = 0x40;
    work2 = g_Task;
    ((s16*)work)[0x10] = 0; // offset 0x20
    ((s32*)work)[0x9]  = 0x1000000; // offset 0x24
    work->vx           = x;
    work->vy           = y;
    work->vz           = z;
    work->unk_1C       = z;
    ((u8*)work2)[1]++;
    SND_PlayCue(0x207);
}
