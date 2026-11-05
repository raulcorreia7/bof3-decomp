#include "area134_13.h"

MATCH void func_801F4624(void) {
    Actor* work;
    Actor* work2;
    Actor* work3;
    u8     count;

    work = (Actor*)g_SpadWork;
    func_801F4E64(&work->vx, work->unk_1C);
    work2 = (Actor*)g_SpadWork;
    work->unk_1C += 0x1199;
    count         = (u8)(work2->unk_09 - 1);
    work2->unk_09 = count;
    if (count == 0) {
        SND_PlayCue(EMI_CUE_ID(2, 15));
        work3 = (Actor*)g_SpadWork;
        work3->unk_01++;
    }
}
