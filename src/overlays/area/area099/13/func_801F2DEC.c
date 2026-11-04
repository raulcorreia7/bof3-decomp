#include "area099_13.h"

MATCH void func_801F2DEC(void) {
    Actor* work;

    work = g_SpadWork;
    if (work->unk_0A != 0) {
        work->y.fixed -= D_801F4990[work->unk_0A & 0xF] << 11;
        work->unk_0A--;
        g_CurrentActor->unk_7E -= 2;
    } else {
        work->unk_04 = 0;
    }
}
