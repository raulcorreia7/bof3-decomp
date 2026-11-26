#include "area134_13.h"

MATCH void func_801F4624(void) {
    Actor* work;
    Actor* work2;
    Actor* work3;
    u8     count;

    work = SELF(Actor);
    func_801F4E64(&work->vx, work->unk_1C);
    work2 = SELF(Actor);
    work->unk_1C += 0x1199;
    count        = (work2->timer - 1);
    work2->timer = count;
    if (count == 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 15));
        work3 = SELF(Actor);
        work3->header.mode++;
    }
}
