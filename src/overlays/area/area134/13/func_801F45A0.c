#include "area134_13.h"

MATCH void func_801F45A0(void) {
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);
    Actor* work;
    s32    sample_y;

    work          = g_Task;
    work->vx      = work->pos.x.fixed + TO_COORD(-1);
    sample_y      = work->pos.y.fixed + TO_COORD(-1);
    work->vy      = sample_y;
    work->vz      = Area_SampleHeight(work->vx, sample_y) << 0x10;
    work->unk_1C  = 0;
    g_Task->timer = 0xA;
    g_Task->header.mode += 1;
}
