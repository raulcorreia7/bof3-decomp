#include "battle_03.h"

/* Advances the active enemy battler's AI state. */
/* nonmatching unmeasured: the byte width of D_800B51F8 is corrected and
 * the enemy-work reads use the EnemyBattler members; candidate 46.94%. resume: the retail homes the slot in s1 (the
 * candidate keeps it in s2) and stores g_Battle.action_type through a pointer materialised before the rand() call. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E25E0(u8 arg0) {
    EnemyBattler* enemy;
    s32           index;
    s32           idx2;
    u8            actor;
    u8            slot;

    slot = arg0;
    g_Battle.action_type =
        ((s32)D_800B51F8[g_BattleEnemyBattlers[slot & BYTE_MASK].choice_ai] >> ((RANDOM_MASK(3)) * 2)) & 3;
    if ((g_Battle.state & BATTLE_STATE_OVER) && (g_BattleEnemyBattlers[slot & BYTE_MASK].stats.intellect < 2U)) {
        g_Battle.action_type = 0;
    }
    if (g_Battle.action_type != 1) {
        if ((s32)g_Battle.action_type < 2) {
            if (g_Battle.action_type != 0) {
                actor = slot & BYTE_MASK;
            } else {
                goto block_17; /* shared state fallback */
            }
        } else if (g_Battle.action_type != 2) {
            index = slot & BYTE_MASK;
            if (g_Battle.action_type != 3) {
                actor = slot & BYTE_MASK;
            } else {
                if (g_BattleEnemyBattlers[index].event_flags & 0x20) {
                    g_Battle.action_type                         = 4;
                    g_BattleEnemyBattlers[index].turn.command.id = g_BattleEnemyBattlers[index].skills[RANDOM_MASK(7)];
                    actor                                        = slot & BYTE_MASK;
                } else {
                    goto block_16; /* shared state fallback */
                }
            }
        } else {
            if (g_BattleEnemyBattlers[slot & BYTE_MASK].event_flags & 0x40) {
                g_Battle.action_type = 3;
            } else {
                goto block_16; /* shared state fallback */
            }
            goto block_18; /* shared state fallback */
        }
    } else {
        idx2 = slot & BYTE_MASK;
        if (g_BattleEnemyBattlers[idx2].event_flags & 0x80) {
            g_Battle.action_type = 2;
            g_BattleEnemyBattlers[idx2].turn.damage_flags.value |= 2;
            actor = slot & BYTE_MASK;
        } else {
        block_16:
        block_17:
            g_Battle.action_type = 1;
        block_18:
            actor = slot & BYTE_MASK;
        }
    }
    if ((g_BattleEnemyBattlers[actor].status & 0x20) ||
        (g_BattleEnemyBattlers[actor].turn.action_flags.value & COMBATANT_FLAG_CHARGING)) {
        g_Battle.action_type = 1;
        if (func_800A9304((slot + 3) & BYTE_MASK) & BYTE_MASK) {
            func_801E2948((s8)actor);
        }
    } else if (func_800A9304((slot + 3) & BYTE_MASK) & BYTE_MASK) {
        g_Battle.target_selector = Battle_PickEnemyTarget(actor);
    }
    if (BATTLE_IS_SCRIPTED()) {
        enemy                = &g_BattleEnemyBattlers[slot & BYTE_MASK];
        g_BattleCurrentEnemy = enemy;
        g_Task               = enemy;
        enemy->unk_E4(0);
    }
    if (g_Battle.target_selector == GAME_NONE) {
        g_Battle.action_type                                      = 0;
        g_BattleEnemyBattlers[slot & BYTE_MASK].turn.command.type = 0;
        return;
    }
    g_BattleEnemyBattlers[slot & BYTE_MASK].turn.command.type = g_Battle.action_type;
}
#else
INCLUDE_ASM(func_801E25E0);
#endif
