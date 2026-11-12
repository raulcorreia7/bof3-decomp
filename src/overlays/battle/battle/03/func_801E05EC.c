#include "battle_03.h"

/* on expiry, runs a flagged response or queues a work slot and
 * increments the active step; otherwise subtracts its deltas, decrements the
 * countdown and runs the next step.
 */
MATCH void func_801E05EC(void) {
    u32          slot;
    PartyMember* work;
    PartyMember* increment_work;
    PartyMember* battle;

    work = g_Task;
    if (work->timer == 0) {
        battle = g_Game.current;
        if (battle->u.turn.target_flags & BATTLE_HIT_HP_LANDED) {
            Battle_QueueAction(battle->u.turn.hp_change, work->slot);
        } else {
            slot                               = Battle_AllocEffect(0U, 1U) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].unk_07       = 3;
            g_BattleEffects[slot].unk_27       = 0;
        }
        increment_work         = g_Task;
        increment_work->unk_03 = increment_work->unk_03 + 1;
        return;
    }
    {
        u8  countdown;
        s32 position_x;
        /* FAKE: pin x delta to a1. */
        FAKE_REG(s32, delta_x, "a1");
        /* FAKE: pin y position to v1. */
        FAKE_REG(s32, position_y, "v1");
        /* FAKE: pin y delta to a2. */
        FAKE_REG(s32, delta_y, "a2");

        /* FAKE: volatile byte view keeps the reload separate from the branch
         * test load. */
        countdown         = VOL(u8, work->timer);
        position_x        = work->pos.x.fixed;
        delta_x           = work->unk_0C;
        position_y        = work->pos.y.fixed;
        delta_y           = work->unk_10;
        countdown         = countdown - 1;
        position_x        = position_x - delta_x;
        position_y        = position_y - delta_y;
        work->pos.x.fixed = position_x;
        work->pos.y.fixed = position_y;
        work->timer       = countdown;
    }
    func_801DEE4C();
}
