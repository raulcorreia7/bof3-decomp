#include "battle_15.h"

void func_800ABCE0(s32 slot, u16 unit, s32 x, s32 y);

MATCH void func_800ABC30(void) {
    s32 loop_count;
    s32 count;

    loop_count         = 0;
    count              = 0;
    g_BattleEnemyCount = 0;
    do {
        if (D_801463DC[loop_count & BYTE_MASK].active != 0) {
            func_800ABCE0(count & BYTE_MASK, D_801463DC[loop_count & BYTE_MASK].id,
                          D_801463DC[loop_count & BYTE_MASK].x, D_801463DC[loop_count & BYTE_MASK].y);
            count += 1;
        }
        loop_count += 1;
    } while ((u32)(loop_count & BYTE_MASK) < 8u);
    g_BattleLivingEnemyCount = g_BattleEnemyCount;
}
