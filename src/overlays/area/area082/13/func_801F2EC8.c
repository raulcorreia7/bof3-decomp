#include "area082_13.h"

MATCH void func_801F2EC8(void) {
    Actor* work = g_SpadWork;

    work->unk_10 += 0x2000;
    work->y.fixed += work->unk_10;
    work->unk_64 -= 6;
    if (work->unk_64 < 8) {
        work->unk_64 = 8;
    }
    g_SpadWork->unk_68 += 6;
    if (--g_SpadWork->unk_2C == 0) {
        Actor_Clear();
    }
}
