#include "boss008_16.h"

MATCH void func_800C19C0(void) {
    s32 idx;
    u32 b0;
    u32 b1;
    u32 b2;
    u32 color;

    if (TASK(PartyMember)->unk_09 == TASK(PartyMember)->timer) {
        idx   = g_BattleCurrentEnemy->unk_F0 - 8;
        b0    = D_800C2640[idx].r >> 3;
        b1    = D_800C2640[idx].g >> 3;
        b2    = D_800C2640[idx].b >> 3;
        color = (b0 << 10) + (b1 << 5);
        func_801D9DBC(0, 0, 11, b2 | color, 1);
        TASK(PartyMember)->timer >>= 1;
    } else {
        TASK(PartyMember)->unk_09 -= 1;
    }
    if (TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->unk_04 += 1;
    }
}
