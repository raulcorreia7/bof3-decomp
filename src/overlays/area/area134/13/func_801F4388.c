#include "area134_13.h"

MATCH void func_801F4388(void) {
    Actor* work;
    Actor* work2;
    s32    x;
    s32    y;
    s32    z;

    Area_ClearWorkColumn();
    work = g_Task;
    x = work->pos.x.fixed;
    y = work->pos.y.fixed;
    z = work->pos.z.fixed;
    work->timer = 0x40;
    work2 = g_Task;
    ((s16*)work)[0x10] = 0;
    ((s32*)work)[0x9]  = 0x1000000;
    work->vx = x;
    work->vy = y;
    work->vz = z;
    work->unk_1C = z;
    ((u8*)work2)[1]++;
    SND_PlayCue(0x208);
}
