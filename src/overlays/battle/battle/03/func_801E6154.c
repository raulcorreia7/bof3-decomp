#include "battle_03.h"

MATCH void func_801E6154(void) {
    BattleEffect* work;
    BattleEffect* new_var;

    work = D_801EC2E0;
    if ((COORD_INT(work->pos.y) >= work->unk_1C) && (work->unk_18 != COORD_INT(work->pos.x))) {
        work->arg.unk_09 = 10;
        D_801EC2E0->header.mode++;
    } else {
        work = new_var = D_801EC2E0;
        work->pos.x.fixed += work->unk_0C;
        new_var->pos.y.fixed += new_var->unk_10;
        new_var->unk_10 += 0x14000;
    }
}
