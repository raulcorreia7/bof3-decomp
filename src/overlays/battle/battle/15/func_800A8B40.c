#include "battle_15.h"

MATCH void func_800A8B40(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    COORD_INT(work->pos.z) += work->unk_14;
    work->pos.z.fixed += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->mode++;
    }
    func_801DEE4C();
}
