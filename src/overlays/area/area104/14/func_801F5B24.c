#include "area104_14.h"

MATCH void func_801F5B24(void) {
    Actor* work;
    u8     count;

    work  = g_Task;
    count = work->unk_0A;
    if (count == 0) {
        work->pos.x.fixed = g_Game.members[0].pos.x.fixed;
        FAKE_BARRIER(); /* FAKE: keeps the y and z loads below the x store */
        work->pos.y.fixed = g_Game.members[0].pos.y.fixed;
        work->pos.z.fixed = D_80145ECC + TO_COORD(128);
        func_801F5BB0(work);
        g_Task->header.mode += 1;
        return;
    }
    work->unk_0A = count - 1;
}
