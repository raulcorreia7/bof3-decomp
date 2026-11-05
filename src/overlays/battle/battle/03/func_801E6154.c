#include "battle_03.h"

MATCH void func_801E6154(void) {
    BattleEffect* work;
    BattleEffect* new_var;

    work = D_801EC2E0;
    if ((work->unk_38.half.hi >= work->unk_1C) && (work->unk_18 != work->unk_34.half.hi)) {
        work->unk_09 = 10;
        D_801EC2E0->mode++;
    } else {
        work = new_var = D_801EC2E0;
        work->unk_34.raw += work->unk_0C;
        new_var->unk_38.raw += new_var->unk_10;
        new_var->unk_10 += 0x14000;
    }
}
