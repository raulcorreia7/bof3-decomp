#include "battle_15.h"

/* FAKE: pin holds the flag constant in v0 and the barrier stops the scheduler
 * sinking it into the load-delay slot, so it fills the bnez delay slot. */
MATCH void func_800A0378(void) {
    u32 mode;
    u16 base;
    /* FAKE: keeps the flag constant in v0 for the bnez delay slot. */
    FAKE_REG(u8, flag, "v0");

    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        mode = *MEM_PTR(u8, &g_Battle.target);
        if (mode < 3u) {
            base = g_Game.members[mode].chr.hp;
        } else {
            base = ENEMY_COMBATANT(mode).hp;
        }
        g_Battle.target_record->hp_change = base;
    } else {
        flag = 1;
        /* FAKE: stops the scheduler sinking the flag into the load-delay slot. */
        FAKE_BARRIER();
        g_Battle.target_record->target_flags = flag;
    }
}
