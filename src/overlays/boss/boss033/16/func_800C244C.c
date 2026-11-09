#include "boss033_16.h"

MATCH void func_800C244C(void) {
    PartyMember* work;

    work = (PartyMember*)g_Task;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    COORD_INT(work->pos.z) += work->unk_14;
    work->pos.z.fixed += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->header.step++;
    }
    Actor_StepAnimOnce();
}
