#include "boss002_16.h"

MATCH void func_800C1A4C(void) {
    EnemyBattler* work;
    u8*           flags;
    u32           limit;
    s32           remaining;

    work      = g_BattleCurrentEnemy;
    remaining = work->hp - work->turn.hp_change;
    limit     = work->stats.max_hp >> 2;
    if (!((s32)limit < remaining)) {
        flags = &g_Battle.boss_flags;
        *flags |= 1;
        work->hp = 65535;
    }
}
