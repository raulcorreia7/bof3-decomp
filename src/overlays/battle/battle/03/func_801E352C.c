#include "battle_03.h"

MATCH void func_801E352C(void) {
    PartyMember* work;
    PartyMember* work2;
    s32          y;
    s16          value;

    Battle_IsEnemyBlocked();
    work = g_Task;
    work->pos.x.fixed += work->unk_0C;
    y                       = work->pos.y.fixed + work->unk_10;
    work->pos.y.fixed       = y;
    value                   = Area_SampleHeight(work->pos.x.fixed, y);
    work2                   = g_Task;
    COORD_INT(work2->pos.z) = value;
    if (work2->pos.x.fixed == work2->unk_18) {
        if (work2->pos.y.fixed == work2->unk_1C) {
            work2->header.mode  = 3;
            g_Task->header.step = 0;
            g_Task->unk_03      = 0;
        }
    }
}
