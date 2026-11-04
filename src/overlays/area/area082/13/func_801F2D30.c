#include "area082_13.h"

MATCH void func_801F2D30(void) {
    Actor* work;
    u16    timer;

    work         = g_SpadWork;
    work->unk_2C = timer = work->unk_2C - 1;
    work->z.fixed += 0x400000;
    work->unk_64 -= 6;
    work->unk_68 += 6;
    if (timer == 0) {
        work->unk_2C = 0x18;
        work->unk_01++;
    }
}
