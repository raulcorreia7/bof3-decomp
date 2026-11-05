#include "boss033_16.h"

MATCH void func_800C1D14(void) {
    EnemyBattler* enemy = g_BattleCurrentEnemy;
    volatile u8*  flag;
    s32           remaining;

    remaining = enemy->hp - FIELD(s16, enemy, 0xF8);
    if ((s32)(enemy->cell_A0.max_hp >> 2) < remaining) {
        return;
    }
    flag = &g_BattleBossFlags;
    *flag |= 0x1;
    enemy->hp = 0xFFFF;
}
