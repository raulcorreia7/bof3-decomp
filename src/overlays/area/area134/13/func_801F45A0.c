#include "area134_13.h"

MATCH void func_801F45A0(void) {
    /* FAKE: unused frame, 16 bytes. */
    STACK_PADS(u8, 16);
    Actor* work;
    s32    sample_y;

    work               = g_SpadWork;
    work->unk_0C       = work->x.fixed + 0xFFFF0000;
    sample_y           = work->y.fixed + 0xFFFF0000;
    work->unk_10       = sample_y;
    work->vz           = Area_SampleHeight(work->unk_0C, sample_y) << 0x10;
    work->unk_1C       = 0;
    g_SpadWork->unk_09 = 0xA;
    g_SpadWork->unk_01 += 1;
}
