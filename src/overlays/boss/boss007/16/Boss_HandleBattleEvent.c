#include "boss007_16.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    u8* text;
    u8* message_state;

    switch ((u8)mode) {
        case BOSS_EVENT_RESTART_BEGIN:
            if ((g_Battle.state & BATTLE_STATE_REPRISAL_PENDING) && (g_Battle.target_selector == 0)) {
                g_BattleBossFlags |= 1;
            }
            break;
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
            text = (u8*)&D_80149298;
            g_BattleResult |= 4;
            g_Game.members[0].u.turn.action_flags.value &= ~COMBATANT_FLAG_DRAGON_FORM;
            SYS_CopyString(text, (u8*)&g_Abilities[ABILITY_WHELP_BREATH], 0xC);
            func_801DE560(1, 1, 0, 0x1E, text);
            message_state               = (u8*)&g_BattleMessageState;
            *message_state              = 1;
            SP_REF(PartyMember*, 0x44u) = &g_Game.members[0];
            Actor_SelectScript(0x2C);
            g_BattleRowCursor   = 0x3C;
            g_Battle.phase.mode = BATTLE_MODE_ROUND_END;
            g_Battle.phase.step = 2;
            break;
        case BOSS_EVENT_TURN_END:
            if (g_BattleResult & 4) {
                g_BattleRowCursor--;
                if ((u8)g_BattleRowCursor != 0) {
                    return BOSS_EVENT_PENDING;
                }
            }
            break;
        case BOSS_EVENT_TICK:
            if (g_Game.members[0].chr.hp == 0) {
                g_Game.members[0].u.turn.action_flags.volatile_value &= ~COMBATANT_FLAG_DRAGON_FORM;
            }
            break;
        case BOSS_EVENT_EFFECTS_LOADED:
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
    }
    return 0;
}
