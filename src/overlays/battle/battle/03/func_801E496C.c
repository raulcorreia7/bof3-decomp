#include "battle_03.h"

MATCH void func_801E496C(void) {
    u16 remainder;
    u16 cap;

    /* The bar's cap is read before the damage, so the test is written cap-first. */
    if (g_BattleCurrentEnemy->hp <= g_BattleCurrentEnemy->turn.hp_change) {
        g_BattleCurrentEnemy->hp     = 0;
        g_BattleCurrentEnemy->status = STATUS_KO;
    } else {
        if (g_BattleCurrentEnemy->turn.hp_change < 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
        }
        remainder                = g_BattleCurrentEnemy->hp - g_BattleCurrentEnemy->turn.hp_change;
        cap                      = g_BattleCurrentEnemy->stats.max_hp;
        g_BattleCurrentEnemy->hp = remainder;
        if (cap < remainder) {
            g_BattleCurrentEnemy->hp = cap;
        }
    }
    if ((g_BattleCurrentEnemy->turn.target_flags & BATTLE_HIT_HP) != 0) {
        Battle_QueueAction(g_BattleCurrentEnemy->turn.hp_change, g_Task->slot);
    }
    Battle_IsEnemyBlocked();
    g_Task->unk_03 = g_Task->unk_03 + 1;
}
