#include "battle_15.h"

void Battle_ArmEnemySlot(s32 slot, u16 unit, s32 x, s32 y);

MATCH void func_800ABC30(void) {
    s32 loop_count;
    s32 count;

    loop_count         = 0;
    count              = 0;
    g_BattleEnemyCount = 0;
    do {
        if (D_801463DC[loop_count & 0xFF].active != 0) {
            Battle_ArmEnemySlot(count & 0xFF, D_801463DC[loop_count & 0xFF].id, D_801463DC[loop_count & 0xFF].x,
                                D_801463DC[loop_count & 0xFF].y);
            count += 1;
        }
        loop_count += 1;
    } while ((loop_count & 0xFF) < 8u);
    g_BattleLivingEnemyCount = g_BattleEnemyCount;
}
