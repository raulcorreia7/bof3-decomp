#include "battle_03.h"

/* Restarts the round step; for a pending reprisal, swaps the acting and saved
 * battler blocks, copies the actor's stats and queues its message.
 */
MATCH void func_801D43EC(void) {
    WorkChunk saved;
    u16*      battle_flags;
    u8        index;
    s32       flags;
    s32       slot;

    battle_flags = &g_Battle.state;
    if ((*battle_flags & 4) && D_801463C2 == 0) {
        *battle_flags &= 0xD7FB;
        g_Battle.phase.step     = 0;
        g_Battle.phase.sub_step = 0;
        if (BATTLE_IS_SCRIPTED()) {
            g_Battle.boss_event_hook(BOSS_EVENT_RESTART_BEGIN);
        }
        if (g_Battle.outcome.result != 0) {
            g_Battle.phase.mode = BATTLE_MODE_ROUND_END;
            g_Battle.phase.step = 2;
            return;
        }
        func_801D4850();
        if (*battle_flags & BATTLE_STATE_REPRISAL_DONE) {
            *battle_flags &= ~BATTLE_STATE_REPRISAL_DONE;
        }
        if (*battle_flags & BATTLE_STATE_REPRISAL_PENDING) {
            saved                                  = *(WorkChunk*)&g_Battle.active_battler;
            *(WorkChunk*)&g_Battle.active_battler  = *(WorkChunk*)&g_Battle.target_selector;
            *(WorkChunk*)&g_Battle.target_selector = saved;
            g_Battle.action_type                   = BATTLE_ACTION_ATTACK;
            index                                  = g_Battle.active_battler;
            if (index < 3) {
                flags                         = g_Game.members[index].u.turn.damage_flags.value;
                *(BattleStatBlock*)D_801EC308 = *(BattleStatBlock*)&g_Game.members[index].chr.stats;
            } else {
                slot                          = index - 3;
                flags                         = g_BattleEnemyBattlers[slot].turn.damage_flags.value;
                *(BattleStatBlock*)D_801EC308 = *(BattleStatBlock*)&g_BattleEnemyBattlers[slot].stats;
            }
            Battle_QueueEvent(1, 0, 0, 0xF, (flags & COMBATANT_FLAG_REPRISAL) ? (u8*)&D_801EB08F : (u8*)&D_801EB04E);
            g_BattleMessageState    = 1;
            g_Battle.phase.step     = 0;
            g_Battle.phase.sub_step = 1;
        }
        if (BATTLE_IS_SCRIPTED()) {
            g_Battle.boss_event_hook(BOSS_EVENT_RESTART_END);
        }
    }
}
