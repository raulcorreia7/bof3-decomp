#include "battle_15.h"

/* Battler status words, one u16 per 0x140-byte player row. */

/* func_8009E98C */
MATCH void Battle_ReviveFullHp(void) {
    volatile u8* state;
    s32          battler;
    /* FAKE: retail materializes the constant in v0 for the branch delay slot. */
    FAKE_REG(s32, selection, "v0");

    state   = &g_Battle.target;
    battler = LOBU(*state);
    if (battler < 3u) {
        if (HAS_STATUS(g_Game.members[battler], STATUS_KO)) {
            do {
                selection = -10000;
            } while (0);
            g_Battle.target_record->hp_change = selection;
            /* FAKE: retail schedules the call arguments after the count store. */
            do {
                g_BattleLivingPartyCount += 1;
            } while (0);
            Battle_CureStatus(*state, 0x4000);
            return;
        }
        g_Battle.target_record->hp_change = 0;
    }
}
