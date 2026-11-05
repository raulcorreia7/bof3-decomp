#include "boss033_16.h"

MATCH void func_800C244C(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->x.raw += work->unk_0C;
    work->y.raw += work->unk_10;
    work->z.half.hi += work->unk_14;
    work->z.raw += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->step++;
    }
    func_8014DAEC();
}
