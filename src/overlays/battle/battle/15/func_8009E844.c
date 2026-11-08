#include "battle_15.h"

/* Base halfwords, one u16 per 0x140-byte player row. */
/* Value halfwords, one u16 per 0x140-byte player row. */

MATCH void func_8009E844(void) {
    volatile u8* slot;
    u8           battler;
    u16          base;

    slot    = &g_Battle.target;
    battler = LOBU(*slot);
    if (BATTLER_IS_PLAYER(battler)) {
        base = g_Game.members[battler].chr.status;
        if ((RANDOM_MASK(3) != 0) && ((base & 0x4000) != 0)) {
            battler = LOBU(*slot);
            if (BATTLER_IS_PLAYER(battler)) {
                g_Battle.target_record->hp_change = (-g_Game.members[battler].chr.stats.max_hp >> 2);
                /* FAKE: retail keeps the selection store before the counter update. */
                FAKE_BARRIER();
                g_Battle.living_party_count++;
            } else {
                g_Battle.target_record->hp_change = (-ENEMY_COMBATANT(battler).stats.max_hp >> 2);
                /* FAKE: retail keeps the selection store before the counter update. */
                FAKE_BARRIER();
                g_Battle.living_enemy_count++;
            }
            func_800A36F0(g_Battle.target, 0x4000);
            return;
        }
        g_Battle.target_record->target_flags = 1;
    }
}
