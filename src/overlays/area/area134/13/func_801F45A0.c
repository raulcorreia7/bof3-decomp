#include "area134_13.h"

MATCH void func_801F45A0(void) {
    /* FAKE: unused frame, 16 bytes. */
    STACK_PADS(u8, 16);
    Actor* work;
    s32    sample_y;

    work           = g_Task;
    work->vx       = work->x.fixed + 0xFFFF0000;
    sample_y       = work->y.fixed + 0xFFFF0000;
    work->vy       = sample_y;
    work->vz       = Area_SampleHeight(work->vx, sample_y) << 0x10;
    work->unk_1C   = 0;
    g_Task->unk_09 = 0xA;
    g_Task->mode += 1;
}
