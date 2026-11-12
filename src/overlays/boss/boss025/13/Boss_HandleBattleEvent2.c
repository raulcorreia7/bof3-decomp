#include "boss025_13.h"

MATCH u8 Boss_HandleBattleEvent2(u32 mode) {
    s16 hp_change;

    switch (mode & BYTE_MASK) {
        case BOSS_EVENT_RESTART_BEGIN:
            if ((g_Battle.active_battler == 3) && (g_Battle.target_selector < 3)) {
                hp_change = g_Game.members[g_Battle.target_selector].u.turn.hp_change;
                if (hp_change > 0) {
                    D_801FE4F0 += hp_change;
                    break;
                }
            }
            if ((g_Battle.target_selector == 3) || (g_Battle.target_selector & BATTLE_TARGET_BOTH_SIDES)) {
                if (!(g_BattleEnemyBattlers[0].turn.damage_flags.value & COMBATANT_FLAG_DEFENDING)) {
                    hp_change = g_BattleEnemyBattlers[0].turn.hp_change;
                    if (hp_change > 0) {
                        D_801FE4E8 += hp_change;
                        break;
                    }
                } else {
                    D_801FE4EF += 1;
                }
            }
            break;
        case BOSS_EVENT_ACTION_START:
            if (g_Battle.turn_cursor != 1) {
                break;
            }
            if (g_BattleEnemyBattlers[0].choice_ai != g_Battle.turn_cursor) {
                break;
            }
            g_BattleEnemyBattlers[0].header.mode       = 2;
            g_BattleEnemyBattlers[0].header.step       = 0;
            g_BattleEnemyBattlers[0].turn.command.type = BATTLE_COMMAND_DEFEND;
            g_BattleEnemyBattlers[0].turn.damage_flags.value |= COMBATANT_FLAG_DEFENDING;
            break;
        case BOSS_EVENT_TURN_END:
            if (D_801463D0 == 21) {
                g_BattleResult |= 4;
            }
            break;
        case BOSS_EVENT_TICK:
            if (g_Battle.boss_flags & 0x20) {
                break;
            }
            if (g_Battle.phase.mode != BATTLE_MODE_COMMANDS) {
                break;
            }
            Battle_AllocEffect(0, 8);
            g_Battle.boss_flags |= 0x20;
            break;
        case BOSS_EVENT_EFFECTS_LOADED:
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}
