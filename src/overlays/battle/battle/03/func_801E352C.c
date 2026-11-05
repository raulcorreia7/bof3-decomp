#include "battle_03.h"

MATCH void func_801E352C(void) {
    PartyBattler* work;
    PartyBattler* work2;
    s32           y;
    s16           value;

    func_801E30F8();
    work = g_Task;
    work->pos.x.fixed += work->unk_0C;
    y                         = work->pos.y.fixed + work->unk_10;
    work->pos.y.fixed         = y;
    value                     = Area_SampleHeight(work->pos.x.fixed, y);
    work2                     = g_Task;
    work2->pos.z.part.integer = value;
    if (work2->pos.x.fixed == work2->unk_18) {
        if (work2->pos.y.fixed == work2->unk_1C) {
            work2->mode    = 3;
            g_Task->step   = 0;
            g_Task->unk_03 = 0;
        }
    }
}
