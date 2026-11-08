#include "battle_03.h"

MATCH void func_801E60DC(void) {
    BattleEffect* slot;
    BattleEffect* work;
    u8            count;

    slot = work = D_801EC2E0;
    slot->pos.y.fixed += TO_COORD(4);
    count            = slot->arg.unk_09;
    slot->arg.unk_09 = count + 0xFF;
    if (count == 0) {
        D_801EC2E0->header.mode += 1;
        slot         = D_801EC2E0;
        slot->unk_0C = 0x8000;
        slot->unk_10 = 0xFFFA0000;
        slot->unk_1C = COORD_INT(slot->pos.y);
        slot->unk_18 = COORD_INT(slot->pos.x);
    }
}
