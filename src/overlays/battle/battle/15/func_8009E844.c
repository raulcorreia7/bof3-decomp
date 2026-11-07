#include "battle_15.h"

/* Base halfwords, one u16 per 0x140-byte player row. */
/* Value halfwords, one u16 per 0x140-byte player row. */
extern u16 D_80145F20[][160];

MATCH void func_8009E844(void) {
    volatile u8* slot;
    u8           battler;
    u16          base;

    slot    = &g_BattleTarget;
    battler = LOBU(*slot);
    if (BATTLER_IS_PLAYER(battler)) {
        base = g_BattlePartyBattlers[battler].chr.status;
        if ((RANDOM_MASK(3) != 0) && ((base & 0x4000) != 0)) {
            battler = LOBU(*slot);
            if (BATTLER_IS_PLAYER(battler)) {
                g_BattleTargetRecord->hp_change = (-D_80145F20[battler][0] >> 2);
                /* FAKE: retail keeps the selection store before the counter update. */
                MATCH_FAKE_BARRIER();
                g_BattleLivingPartyCount++;
            } else {
                g_BattleTargetRecord->hp_change = (-ENEMY_COMBATANT(battler).stats.max_hp >> 2);
                /* FAKE: retail keeps the selection store before the counter update. */
                MATCH_FAKE_BARRIER();
                g_BattleLivingEnemyCount++;
            }
            func_800A36F0(g_BattleTarget, 0x4000);
            return;
        }
        g_BattleTargetRecord->target_flags = 1;
    }
}
