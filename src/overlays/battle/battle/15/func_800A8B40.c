#include "battle_15.h"

MATCH void func_800A8B40(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_Task;
    work->coord_x_34.raw += work->unk_0C;
    work->coord_y_38.raw += work->unk_10;
    work->word_3C.half.span_3E += work->unk_14;
    work->word_3C.word += work->unk_18;
    work->unk_14 += work->unk_20;
    if (work->unk_14 == -0x40) {
        work->mode++;
    }
    func_801DEE4C();
}
