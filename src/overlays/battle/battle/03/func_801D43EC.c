#include "battle_03.h"

/* Restarts the battle: clears the pending step, swaps the battle
 * state with the saved one and refreshes the actors' status rows.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801D43EC(void) {
    s32  saved0;
    s32  saved1;
    s32  saved2;
    s32  saved3;
    s32  index;
    s32  flags;
    u16* battle_flags;
    s32* block74;
    s32* block84;

    battle_flags = &g_Battle.state;
    if ((*battle_flags & 4) && (D_801463C2 == 0)) {
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
            block74              = (s32*)&g_Battle.active_battler;
            block84              = (s32*)&g_Battle.target_selector;
            saved0               = block74[0];
            saved1               = block74[1];
            saved2               = block74[2];
            saved3               = block74[3];
            block74[0]           = block84[0];
            block74[1]           = block84[1];
            block74[2]           = block84[2];
            block74[3]           = block84[3];
            block84[0]           = saved0;
            block84[1]           = saved1;
            block84[2]           = saved2;
            block84[3]           = saved3;
            g_Battle.action_type = BATTLE_ACTION_ATTACK;
            index                = g_Battle.active_battler;
            if ((u8)index < 3U) {
                *(BattleStatBlock*)D_801EC308 = *(BattleStatBlock*)(D_80145F20 + index * 0x140 + 3);
                flags                         = g_Game.members[index].turn.damage_flags.value & COMBATANT_FLAG_REPRISAL;
            } else {
                /* The party side reads the same block three bytes in; one address keeps both reads alike. */
                *(BattleStatBlock*)D_801EC308 = *(BattleStatBlock*)(D_801EB6D0 + 3);
                flags                         = ENEMY_COMBATANT(index).turn.damage_flags.value & COMBATANT_FLAG_REPRISAL;
            }
            if (flags != 0) {
                Battle_QueueEvent(1, 0, 0, 0xF, (u8*)&D_801EB08F);
            } else {
                Battle_QueueEvent(1, 0, 0, 0xF, (u8*)&D_801EB04E);
            }
            g_BattleMessageState    = 1;
            g_Battle.phase.step     = 0;
            g_Battle.phase.sub_step = 1;
        }
        if (BATTLE_IS_SCRIPTED()) {
            g_Battle.boss_event_hook(BOSS_EVENT_RESTART_END);
        }
    }
}
#else
INCLUDE_ASM(func_801D43EC);
#endif
