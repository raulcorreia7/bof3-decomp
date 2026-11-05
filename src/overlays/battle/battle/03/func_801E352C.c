#include "battle_03.h"

MATCH void func_801E352C(void) {
    PartyBattler* work;
    PartyBattler* work2;
    s32           y;
    s16           value;

    func_801E30F8();
    work = g_Task;
    work->coord_x_34.raw += work->unk_0C;
    y                           = work->coord_y_38.raw + work->unk_10;
    work->coord_y_38.raw        = y;
    value                       = Area_SampleHeight(work->coord_x_34.raw, y);
    work2                       = g_Task;
    work2->word_3C.half.span_3E = value;
    if (work2->coord_x_34.raw == work2->unk_18) {
        if (work2->coord_y_38.raw == work2->unk_1C) {
            work2->mode    = 3;
            g_Task->step   = 0;
            g_Task->unk_03 = 0;
        }
    }
}
