#include "battle_03.h"

/* Advances the active enemy battler's AI state: rolls the next state from its behavior row, gates it on
 * health and flags, then dispatches the state update and records it.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801E25E0(u8 battler) {
    EnemyBattler* enemy;

    g_Battle.action_type = ((s32)D_800B51F8[g_BattleEnemyBattlers[battler].choice_ai] >> ((RANDOM_MASK(3)) * 2)) & 3;
    if ((g_Battle.state & BATTLE_STATE_OVER) && (g_BattleEnemyBattlers[battler].stats.intellect < 2U)) {
        g_Battle.action_type = 0;
    }
    if (g_Battle.action_type != 1) {
        if ((s32)g_Battle.action_type < 2) {
            if (g_Battle.action_type != 0) {
            } else {
                goto block_17; /* shared state fallback */
            }
        } else if (g_Battle.action_type != 2) {
            if (g_Battle.action_type != 3) {
            } else {
                if (g_BattleEnemyBattlers[battler].event_flags & 0x20) {
                    g_Battle.action_type                           = 4;
                    g_BattleEnemyBattlers[battler].turn.command.id = g_BattleEnemyBattlers[battler].skills[RANDOM_MASK(7)];
                } else {
                    goto block_16; /* shared state fallback */
                }
            }
        } else {
            if (g_BattleEnemyBattlers[battler].event_flags & 0x40) {
                g_Battle.action_type = 3;
            } else {
                goto block_16; /* shared state fallback */
            }
            goto block_18; /* shared state fallback */
        }
    } else {
        if (g_BattleEnemyBattlers[battler].event_flags & 0x80) {
            g_Battle.action_type = 2;
            g_BattleEnemyBattlers[battler].turn.damage_flags.value |= 2;
        } else {
        block_16:
        block_17:
            g_Battle.action_type = 1;
        block_18:
        }
    }
    if ((g_BattleEnemyBattlers[battler].status & 0x20) || (g_BattleEnemyBattlers[battler].turn.action_flags.value & COMBATANT_FLAG_CHARGING)) {
        g_Battle.action_type = 1;
        if (func_800A9304((battler + 3) & BYTE_MASK) & BYTE_MASK) {
            func_801E2948((s8)battler);
        }
    } else if (func_800A9304((battler + 3) & BYTE_MASK) & BYTE_MASK) {
        g_Battle.target_selector = Battle_PickEnemyTarget(battler);
    }
    if (BATTLE_IS_SCRIPTED()) {
        enemy                = &g_BattleEnemyBattlers[battler];
        g_BattleCurrentEnemy = enemy;
        g_Task               = enemy;
        enemy->unk_E4(0);
    }
    if (g_Battle.target_selector == GAME_NONE) {
        g_Battle.action_type                             = 0;
        g_BattleEnemyBattlers[battler].turn.command.type = 0;
        return;
    }
    g_BattleEnemyBattlers[battler].turn.command.type = g_Battle.action_type;
}
#else
INCLUDE_ASM(func_801E25E0);
#endif
