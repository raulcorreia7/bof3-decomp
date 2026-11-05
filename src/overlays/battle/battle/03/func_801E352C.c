#include "battle_03.h"

MATCH void func_801E352C(void) {
    PartyBattler* work;
    PartyBattler* work2;
    s32           y;
    s16           value;

    func_801E30F8();
    work = g_Task;
    work->x.raw += work->unk_0C;
    y                = work->y.raw + work->unk_10;
    work->y.raw      = y;
    value            = Area_SampleHeight(work->x.raw, y);
    work2            = g_Task;
    work2->z.half.hi = value;
    if (work2->x.raw == work2->unk_18) {
        if (work2->y.raw == work2->unk_1C) {
            work2->mode    = 3;
            g_Task->step   = 0;
            g_Task->unk_03 = 0;
        }
    }
}
