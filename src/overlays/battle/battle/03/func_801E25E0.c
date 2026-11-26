#include "battle_03.h"

/* Advances the active enemy battler's AI state: rolls the next state from its behavior row, gates it on
 * health and flags, then dispatches the state update and records it.
 */
MATCH void func_801E25E0(u8 battler) {
    EnemyBattler* enemy;

    g_Battle.action_type = (D_800B51F8[g_BattleEnemyBattlers[battler].choice_ai] >> ((rand() & 3) * 2)) & 3;
    if ((g_Battle.flags & BATTLE_STATE_OVER) && g_BattleEnemyBattlers[battler].stats.intelligence < 2) {
        g_Battle.action_type = 0;
    }
    switch (g_Battle.action_type) {
        case 0:
            g_Battle.action_type = 1;
            break;
        case 1:
            if (g_BattleEnemyBattlers[battler].event_flags & 0x80) {
                g_Battle.action_type = 2;
                g_BattleEnemyBattlers[battler].turn.damage_flags.value |= 2;
            } else {
                g_Battle.action_type = 1;
            }
            break;
        case 2:
            if (g_BattleEnemyBattlers[battler].event_flags & 0x40) {
                g_Battle.action_type = 3;
            } else {
                g_Battle.action_type = 1;
            }
            break;
        case 3:
            if (g_BattleEnemyBattlers[battler].event_flags & 0x20) {
                g_Battle.action_type                           = 4;
                g_BattleEnemyBattlers[battler].turn.command.id = g_BattleEnemyBattlers[battler].skills[rand() & 7];
            } else {
                g_Battle.action_type = 1;
            }
            break;
    }
    if ((g_BattleEnemyBattlers[battler].status & 0x20) || (g_BattleEnemyBattlers[battler].turn.action_flags.value & BATTLER_ACTION_CHARGING)) {
        g_Battle.action_type = 1;
        if (func_800A9304(battler + 3)) {
            /* FAKE: retail passes the masked slot, which the s8 prototype would sign-extend. */
            ((void (*)(u8))func_801E2948)(battler);
        }
    } else if (func_800A9304(battler + 3)) {
        g_Battle.target_selector = Battle_PickEnemyTarget(battler);
    }
    if (BATTLE_IS_SCRIPTED()) {
        enemy                = &g_BattleEnemyBattlers[battler];
        g_BattleCurrentEnemy = enemy;
        SELF_SET(enemy);
        enemy->unk_E4(0);
    }
    if (g_Battle.target_selector == GAME_NONE) {
        g_Battle.action_type                             = 0;
        g_BattleEnemyBattlers[battler].turn.command.type = 0;
    } else {
        g_BattleEnemyBattlers[battler].turn.command.type = g_Battle.action_type;
    }
}
