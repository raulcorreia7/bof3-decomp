#include "battle_03.h"

MATCH void func_801E496C(void) {
    u16 remainder;
    u16 cap;

    /* The bar's cap is read before the damage, so the test is written cap-first. */
    if ((s32)g_BattleCurrentEnemy->hp <= g_BattleCurrentEnemy->damage) {
        g_BattleCurrentEnemy->hp     = 0;
        g_BattleCurrentEnemy->status = STATUS_KO;
    } else {
        if (g_BattleCurrentEnemy->damage < 0) {
            SND_PlayCue(EMI_CUE_ID(2, 6));
        }
        remainder                = g_BattleCurrentEnemy->hp - (u16)g_BattleCurrentEnemy->damage;
        cap                      = g_BattleCurrentEnemy->cell_A0.max_hp;
        g_BattleCurrentEnemy->hp = remainder;
        if (cap < remainder) {
            g_BattleCurrentEnemy->hp = cap;
        }
    }
    if ((g_BattleCurrentEnemy->target_flags & 1) != 0) {
        func_800AAC88(g_BattleCurrentEnemy->damage, g_Task->slot);
    }
    func_801E30F8();
    g_Task->unk_03 = g_Task->unk_03 + 1;
}
