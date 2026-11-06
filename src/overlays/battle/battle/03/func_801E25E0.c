#include "battle_03.h"

/* Advances the active enemy battler's AI state: rolls the next state from its behavior row, gates it on
 * health and flags, then dispatches the state update and records it.
 */
/* nonmatching unmeasured: the byte widths of D_800B51F8, D_801EB6AE, D_801EB6BC and D_801EB725 are corrected and
 * the enemy-work reads use the EnemyBattler members; candidate 46.94%. resume: the retail homes the slot in s1 (the
 * candidate keeps it in s2) and stores g_BattleActionType through a pointer materialised before the rand() call. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E25E0(u8 arg0) {
    EnemyBattler* enemy;
    s32           idx;
    s32           idx2;
    s32           row2;
    s32           row3;
    u8            actor;
    u8            slot;

    slot               = arg0;
    g_BattleActionType = ((s32)D_800B51F8[g_BattleEnemyBattlers[slot & BYTE_MASK].choice_ai] >> ((rand() & 3) * 2)) & 3;
    if ((g_BattleState & BATTLE_STATE_OVER) && (g_BattleEnemyBattlers[slot & BYTE_MASK].stats.intellect < 2U)) {
        g_BattleActionType = 0;
    }
    if (g_BattleActionType != 1) {
        if ((s32)g_BattleActionType < 2) {
            if (g_BattleActionType != 0) {
                actor = slot & BYTE_MASK;
            } else {
                goto block_17; /* shared state fallback */
            }
        } else if (g_BattleActionType != 2) {
            idx = slot & BYTE_MASK;
            if (g_BattleActionType != 3) {
                actor = slot & BYTE_MASK;
            } else {
                actor = idx * 0x118;
                if (*D_801EB6B0[idx] & 0x20) {
                    g_BattleActionType = 4;
                    *D_801EB726[idx]   = D_801EB6BC[actor + (rand() & 7)];
                    actor              = slot & BYTE_MASK;
                } else {
                    goto block_16; /* shared state fallback */
                }
            }
        } else {
            if (*D_801EB6B0[slot & BYTE_MASK] & 0x40) {
                g_BattleActionType = 3;
            } else {
                goto block_16; /* shared state fallback */
            }
            goto block_18; /* shared state fallback */
        }
    } else {
        idx2 = slot & BYTE_MASK;
        row3 = idx2 * 0x118;
        if (*D_801EB6B0[idx2] & 0x80) {
            g_BattleActionType   = 2;
            *(D_801EB730 + row3) = *(D_801EB730 + row3) | 2;
            actor                = slot & BYTE_MASK;
        } else {
        block_16:
        block_17:
            g_BattleActionType = 1;
        block_18:
            actor = slot & BYTE_MASK;
        }
    }
    row2 = actor * 0x118;
    if ((*(D_801EB6B2 + row2) & 0x20) || (g_BattleEnemyBattlers[actor].action_flags & COMBATANT_FLAG_CHARGING)) {
        g_BattleActionType = 1;
        if (func_800A9304((slot + 3) & BYTE_MASK) & BYTE_MASK) {
            func_801E2948((s8)actor);
        }
    } else if (func_800A9304((slot + 3) & BYTE_MASK) & BYTE_MASK) {
        g_BattleTargetSelector = Battle_PickEnemyTarget(actor);
    }
    if (g_BattleEncounter != 0) {
        enemy                = &g_BattleEnemyBattlers[slot & BYTE_MASK];
        g_BattleCurrentEnemy = enemy;
        g_Task               = enemy;
        enemy->unk_E4(0);
    }
    if (g_BattleTargetSelector == GAME_NONE) {
        g_BattleActionType                             = 0;
        g_BattleEnemyBattlers[slot & BYTE_MASK].unk_F5 = 0;
        return;
    }
    g_BattleEnemyBattlers[slot & BYTE_MASK].unk_F5 = g_BattleActionType;
}
#else
INCLUDE_ASM(func_801E25E0);
#endif
