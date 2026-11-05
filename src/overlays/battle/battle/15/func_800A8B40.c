#include "battle_15.h"

MATCH void func_800A8B40(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->x.raw += work->unk_0C;
    work->y.raw += work->unk_10;
    work->z.half.hi += work->unk_14;
    work->z.raw += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->mode++;
    }
    func_801DEE4C();
}
