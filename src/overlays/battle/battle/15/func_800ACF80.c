#include "battle_15.h"

MATCH void func_800ACF80(void) {
    u8 i;

    for (i = 0; i < 8; i++) {
        g_BattleEnemyBattlers[i].flags  = 0;
        g_BattleEnemyBattlers[i].mode   = 0;
        g_BattleEnemyBattlers[i].step   = 0;
        g_BattleEnemyBattlers[i].unk_03 = 0;
        g_BattleEnemyBattlers[i].unk_04 = 0;
    }
}
