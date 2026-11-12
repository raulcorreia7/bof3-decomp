#include "boss008_16.h"

MATCH void func_800C19C0(void) {
    s32 idx;
    u32 b0;
    u32 b1;
    u32 b2;
    u32 color;

    if (g_Task->unk_09 == g_Task->timer) {
        idx   = (g_BattleCurrentEnemy->unk_F0 - 8) * 3;
        b0    = D_800C2640[idx] >> 3;
        b1    = D_800C2641[idx] >> 3;
        b2    = D_800C2642[idx] >> 3;
        color = (b0 << 10) + (b1 << 5);
        func_801D9DBC(0, 0, 11, b2 | color, 1);
        g_Task->timer >>= 1;
    } else {
        g_Task->unk_09 -= 1;
    }
    if (g_Task->unk_09 == 0) {
        g_Task->unk_04 += 1;
    }
}
