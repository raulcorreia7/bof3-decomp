#include "battle_03.h"

/* on expiry, runs a flagged response or queues a work slot and
 * increments the active step; otherwise subtracts its deltas, decrements the
 * countdown and runs the next step.
 */
MATCH void func_801E05EC(void) {
    u32           slot;
    PartyBattler* work;
    PartyBattler* increment_work;
    PartyBattler* battle;

    work = g_SpadWork;
    if (work->unk_0A == 0) {
        battle = g_GameState;
        if (battle->unk_120 & 0x10) {
            func_800AAC88((s16)battle->hp_change, work->slot);
        } else {
            slot                                = Battle_AllocEffect(0U, 1U) & BYTE_MASK;
            g_BattleEffects[slot].work_74.party = g_SpadWork;
            g_BattleEffects[slot].unk_07        = 3;
            g_BattleEffects[slot].unk_27        = 0;
        }
        increment_work         = g_SpadWork;
        increment_work->unk_03 = increment_work->unk_03 + 1;
        return;
    }
    {
        u8  countdown;
        s32 position_x;
        /* FAKE: pin x delta to a1. */
        MATCH_REG(s32, delta_x, "a1");
        /* FAKE: pin y position to v1. */
        MATCH_REG(s32, position_y, "v1");
        /* FAKE: pin y delta to a2. */
        MATCH_REG(s32, delta_y, "a2");

        /* FAKE: volatile byte view keeps the reload separate from the branch
         * test load. */
        countdown            = VOL(u8, work->unk_0A);
        position_x           = work->coord_x_34.raw;
        delta_x              = work->unk_0C;
        position_y           = work->coord_y_38.raw;
        delta_y              = work->unk_10;
        countdown            = countdown - 1;
        position_x           = position_x - delta_x;
        position_y           = position_y - delta_y;
        work->coord_x_34.raw = position_x;
        work->coord_y_38.raw = position_y;
        work->unk_0A         = countdown;
    }
    func_801DEE4C();
}
