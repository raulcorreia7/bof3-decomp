#include "battle_15.h"

/* Battler status words, one u16 per 0x140-byte player row. */

MATCH void func_8009E98C(void) {
    volatile u8* state;
    s32          battler;
    /* FAKE: retail materializes the constant in v0 for the branch delay slot. */
    MATCH_REG(s32, selection, "v0");

    state   = &g_BattleTarget;
    battler = LOBU(*state);
    if (battler < 3u) {
        if (HAS_STATUS(g_BattlePartyBattlers[battler], STATUS_KO)) {
            ORDER_LOCK(selection = -0x2710);
            g_BattleTargetRecord->hp_change = selection;
            /* FAKE: retail schedules the call arguments after the count store. */
            ORDER_LOCK(g_BattleLivingPartyCount += 1);
            func_800A36F0(*state, 0x4000);
            return;
        }
        g_BattleTargetRecord->hp_change = 0;
    }
}
