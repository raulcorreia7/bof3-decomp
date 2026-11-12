#include "area082_13.h"

MATCH void func_801F2EC8(void) {
    Actor* work = g_Task;

    work->vy += 8192;
    work->pos.y.fixed += work->vy;
    work->unk_64 -= 6;
    if (work->unk_64 < 8) {
        work->unk_64 = 8;
    }
    g_Task->unk_68 += 6;
    if (--g_Task->unk_2C == 0) {
        Actor_Clear();
    }
}
