#include "battle_15.h"

MATCH void func_800A8B40(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->pos.x.raw += work->unk_0C;
    work->pos.y.raw += work->unk_10;
    work->pos.z.half.hi += work->unk_14;
    work->pos.z.raw += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->mode++;
    }
    func_801DEE4C();
}
