#include "battle_03.h"

MATCH void func_801E60DC(void) {
    BattleEffect* slot;
    BattleEffect* work;
    u8            count;

    slot = work = D_801EC2E0;
    slot->unk_38.raw += 0x40000;
    count        = slot->unk_09;
    slot->unk_09 = count + 0xFF;
    if (count == 0) {
        D_801EC2E0->mode += 1;
        slot         = D_801EC2E0;
        slot->unk_0C = 0x8000;
        slot->unk_10 = (s32)0xFFFA0000;
        slot->unk_1C = slot->unk_38.half.hi;
        slot->unk_18 = slot->unk_34.half.hi;
    }
}
