#include "battle_03.h"

/* FAKE: LOBU reads g_Battle.action_type without the volatile `andi` retail does not carry;
 * the plain volatile name does not match.
 */

/* runs the queued step: while not retreating and the enemy's spin flag is set it clears the gate and arms
 * the retreat; otherwise it re-arms the gate from the kind and flag records and reseeds the step and tint fields.
 */
MATCH void func_801E020C(void) {
    PartyMember* work;

    Battle_IsPartyMemberBlocked();
    work = g_Task;
    if ((work->header.step != 3) && (HAS_STATUS(*g_Game.current, STATUS_KO))) {
        /* FAKE: half pointer; the direct global scores 97.37%. */
        u16* half;
        half = &g_Battle.state;
        *half &= ~BATTLE_STATE_REPRISAL_PENDING;
        g_Task->header.mode = 6;
        g_Task->header.step = 4;
    } else {
        /* FAKE: half pointer; the direct global scores 82.24%. */
        u16* half;
        half = &g_Battle.state;
        if ((*half & BATTLE_STATE_REPRISAL_PENDING) == 0) {
            if ((g_Battle.target_selector & BATTLE_TARGET_BOTH_SIDES) == 0) {
                if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ATTACK) {
                    if ((func_801DD448() & BYTE_MASK) != 0) {
                        *half |= BATTLE_STATE_REPRISAL_PENDING;
                    }
                }
                if ((LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) && ((D_801CA71C[g_Battle.action_id].mask & 0x800) != 0) && ((func_801DD448() & BYTE_MASK) != 0) &&
                    ((D_801CA718[g_Battle.action_id][0] & ABILITY_TARGET_ALL) == 0)) {
                    g_Battle.state |= BATTLE_STATE_REPRISAL_PENDING;
                }
            }
        } else {
            *half = (*half & ~BATTLE_STATE_REPRISAL_PENDING) | BATTLE_STATE_REPRISAL_DONE;
        }
        Battle_ClearSlotPending(g_Task->slot);
        g_Game.current->u.turn.damage_flags.value &= ~(COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED);
        if ((func_801E0E0C() & BYTE_MASK) != 0) {
            /* FAKE: flag pointer; the direct store scores 97.37%. */
            volatile u8* flag;
            flag = &g_Battle.outcome.result;
            *flag |= 1;
        }
        g_Game.current->u.turn.damage_flags.value &= ~COMBATANT_FLAG_DAMAGE_ROW_PRESENT;
        g_Task->header.mode = 2;
        g_Task->header.step = 0;
    }
    g_Task->unk_03 = 0;
}
