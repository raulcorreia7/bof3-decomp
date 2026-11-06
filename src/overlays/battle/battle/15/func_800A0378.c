#include "battle_15.h"

/* FAKE: pin holds the flag constant in v0 and the barrier stops the scheduler
 * sinking it into the load-delay slot, so it fills the bnez delay slot. */
MATCH void func_800A0378(void) {
    u32 mode;
    u16 base;
    /* FAKE: keeps the flag constant in v0 for the bnez delay slot. */
    MATCH_FAKE_PIN(u8, flag, "v0");

    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        mode = *MEM_PTR(u8, &g_BattleTarget);
        if (mode < 3u) {
            base = g_BattlePartyBattlers[mode].chr.hp;
        } else {
            base = ENEMY_COMBATANT(mode).hp;
        }
        g_BattleTargetRecord->hp_change = base;
    } else {
        flag = 1;
        /* FAKE: stops the scheduler sinking the flag into the load-delay slot. */
        MATCH_FAKE_BARRIER();
        g_BattleTargetRecord->target_flags = flag;
    }
}
