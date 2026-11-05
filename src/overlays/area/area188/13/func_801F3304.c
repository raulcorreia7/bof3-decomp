#include "area188_13.h"

MATCH void func_801F3304(void) {
    Actor* work;
    s32*   pos;
    s32    z;

    work         = g_SpadWork;
    pos          = D_80145EC4;
    work->unk_64 = pos[0];
    work->unk_68 = pos[1];
    z            = pos[2] + 0x800000;
    work->unk_09 = 8;
    work->unk_2E = 0;
    work->unk_6C = z;
    g_SpadWork->unk_01++;
}
