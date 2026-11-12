#include "boss033_16.h"

MATCH void func_800C1D14(void) {
    EnemyBattler* enemy = g_BattleCurrentEnemy;
    volatile u8*  flag;
    s32           remaining;

    remaining = enemy->hp - FIELD(s16, enemy, 0xF8);
    if ((enemy->stats.max_hp >> 2) < remaining) {
        return;
    }
    flag = &g_Battle.boss_flags;
    *flag |= 0x1;
    enemy->hp = 65535;
}
