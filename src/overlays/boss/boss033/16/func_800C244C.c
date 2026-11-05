#include "boss033_16.h"

MATCH void func_800C244C(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->coord_x_34.raw += work->unk_0C;
    work->coord_y_38.raw += work->unk_10;
    work->word_3C.half.span_3E += work->unk_14;
    work->word_3C.word += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->step++;
    }
    func_8014DAEC();
}
