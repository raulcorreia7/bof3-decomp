#include "battle_03.h"

extern u8 D_801EC308[];

/* Restarts the battle: clears the pending step, swaps the battle
 * state with the saved one and refreshes the actors' status rows.
 */
/* nonmatching unmeasured: tried the four swapped state words are not kept in stack slots, so the frame is 0x28 against
 * the retail 0x30 and the candidate is 124 bytes short. resume: a source shape that keeps the four swapped words in
 * stack slots and drops the extra saved register. */
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

    battle_flags = &g_BattleState;
    if ((*battle_flags & 4) && (D_801463C2 == 0)) {
        *battle_flags &= 0xD7FB;
        g_BattleStep    = 0;
        g_BattleSubStep = 0;
        if (g_BattleEncounter != 0) {
            g_BossBattleEventHook(0U);
        }
        if (g_BattleResult != 0) {
            g_BattleMode = 4;
            g_BattleStep = 2;
            return;
        }
        func_801D4850();
        if (*battle_flags & BATTLE_STATE_REPRISAL_DONE) {
            *battle_flags &= ~BATTLE_STATE_REPRISAL_DONE;
        }
        if (*battle_flags & BATTLE_STATE_REPRISAL_PENDING) {
            block74            = (s32*)&g_BattleActiveBattler;
            block84            = (s32*)&g_BattleTargetSelector;
            saved0             = block74[0];
            saved1             = block74[1];
            saved2             = block74[2];
            saved3             = block74[3];
            block74[0]         = block84[0];
            block74[1]         = block84[1];
            block74[2]         = block84[2];
            block74[3]         = block84[3];
            block84[0]         = saved0;
            block84[1]         = saved1;
            block84[2]         = saved2;
            block84[3]         = saved3;
            g_BattleActionType = BATTLE_ACTION_ATTACK;
            index              = g_BattleActiveBattler;
            if ((u8)index < 3U) {
                *(BattleStatBlock*)D_801EC308 = *(BattleStatBlock*)(D_80145F20 + index * 0x140 + 3);
                flags = g_BattlePartyBattlers[index].turn.damage_flags.value & COMBATANT_FLAG_REPRISAL;
            } else {
                *(BattleStatBlock*)D_801EC308 = *(BattleStatBlock*)(D_801EB6D0 + 3);
                flags                         = *(u32*)(D_801EB730 + (index - 3) * 0x118) & 0x8000;
            }
            if (flags != 0) {
                func_801DE560(1, 0, 0, 0xF, (u8*)&D_801EB08F);
            } else {
                func_801DE560(1, 0, 0, 0xF, (u8*)&D_801EB04E);
            }
            g_BattleMessageState = 1;
            g_BattleStep         = 0;
            g_BattleSubStep      = 1;
        }
        if (g_BattleEncounter != 0) {
            g_BossBattleEventHook(5U);
        }
    }
}
#else
INCLUDE_ASM(func_801D43EC);
#endif
