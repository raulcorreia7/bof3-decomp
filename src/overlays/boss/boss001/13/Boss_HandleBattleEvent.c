#include "boss001_13.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    switch ((u8)mode) {
        case BOSS_EVENT_ACTION_START:
            if (g_Battle.active_battler != 0) {
                break;
            }
            if (g_Battle.action_type != BATTLE_ACTION_ABILITY) {
                break;
            }
            if (g_Battle.action->unk_02 != ABILITY_WHELP_BREATH) {
                break;
            }
            g_BattleEnemyBattlers[0].hp           = 1;
            g_BattleEnemyBattlers[0].stats.max_hp = 1;
            g_BattleEnemyBattlers[1].hp           = 1;
            g_BattleEnemyBattlers[1].stats.max_hp = 1;
            g_Game.members[0].u.turn.action_flags.value &= ~COMBATANT_FLAG_DRAGON_FORM;
            break;
        case BOSS_EVENT_RESTART_BEGIN:
            if ((g_Battle.state & BATTLE_STATE_REPRISAL_PENDING) && (g_Battle.target_selector == 0)) {
                g_BattleBossFlags |= 1;
            }
            break;
        case BOSS_EVENT_RESTART_END:
            if (g_BattleBossFlags & 1) {
                g_Game.members[0].u.turn.command.type   = BATTLE_ACTION_ABILITY;
                g_Battle.action_type                    = BATTLE_ACTION_ABILITY;
                g_Game.members[0].u.turn.command.target = BATTLE_TARGET_ENEMY_SIDE;
                g_Battle.target_selector                = BATTLE_TARGET_ENEMY_SIDE;
                g_Game.members[0].u.turn.command.id     = ABILITY_WHELP_BREATH;
            }
            break;
        case BOSS_EVENT_BATTLE_RESET:
            g_Game.members[0].u.turn.action_flags.value |= COMBATANT_FLAG_DRAGON_FORM;
            break;
        case BOSS_EVENT_TURN_END:
        case BOSS_EVENT_TICK:
        case BOSS_EVENT_EFFECTS_LOADED:
            break;
    }
    return 0;
}
