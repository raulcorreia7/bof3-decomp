#include "area104_14.h"

MATCH void func_801F5B24(void) {
    Actor* work;
    u8     count;

    work  = g_SpadWork;
    count = work->unk_0A;
    if (count == 0) {
        work->x.fixed = D_80145EC4;
        MATCH_FAKE_BARRIER(); /* FAKE: keeps the y and z loads below the x store */
        work->y.fixed = D_80145EC8;
        work->z.fixed = D_80145ECC + 0x800000;
        func_801F5BB0(work);
        g_SpadWork->unk_01 += 1;
        return;
    }
    work->unk_0A = count - 1;
}
