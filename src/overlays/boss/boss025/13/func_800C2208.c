#include "boss025_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_800C2208(u32 mode) {
    switch ((u8)mode) {
        case BOSS_EVENT_TICK:
            if (!(g_Battle.boss_flags & 0x20) && (g_Battle.phase.mode == BATTLE_MODE_COMMANDS)) {
                Battle_AllocEffect(0, 8);
                g_Battle.boss_flags |= 0x20;
            }
            if (!(g_Battle.boss_flags & 0x10) && (*(u16*)&g_Battle.phase == BATTLE_MODE_TURNS)) {
                g_Game.members[0].u.turn.command.type      = BATTLE_ACTION_ATTACK;
                g_Game.members[0].chr.stats.accuracy       = 100;
                g_BattleEnemyBattlers[0].turn.command.type = 2;
                g_Battle.turn_count                        = 7;
                g_BattleEnemyBattlers[0].turn.damage_flags.value |= 2;
                g_Game.members[0].u.turn.command.target      = 3;
                g_Battle.turn_order[1]                       = 3;
                g_Battle.turn_order[3]                       = 3;
                g_Battle.turn_order[5]                       = 3;
                g_Game.members[0].chr.stats.critical_chance  = 0;
                g_BattleEnemyBattlers[0].turn.command.target = 0;
                g_Battle.turn_order[0]                       = 0;
                g_Battle.turn_order[2]                       = 0;
                g_Battle.turn_order[4]                       = 0;
                g_Battle.turn_order[6]                       = 0;
                g_Battle.boss_flags |= 0x10;
            }
            if (!(g_Battle.boss_flags & 1)) {
                g_MenuPanelMode = 2;
                Message_StartAreaMessage(0x19);
                g_Battle.boss_flags |= 1;
                break;
            }
            if (!(g_Battle.boss_flags & 2)) {
                SP_REF(PartyMember*, 0x44u) = &g_BattleEnemyBattlers[0];
                func_801E2314(8);
                g_Battle.boss_flags |= 2;
                break;
            }
            if ((D_801462EC & 0x600) == 0x200) {
                g_MenuPanelMode = 2;
                Message_StartAreaMessage(0x1A);
                g_Battle.boss_flags |= 4;
                break;
            }
            if (g_Battle.turn_cursor == 4) {
                if ((*(u32*)g_Game.members & 0xFFFF00) == 0x10600) {
                    g_Battle.action_type               = 0xFF;
                    g_Game.members[0].u.turn.hp_change = 0;
                    g_Game.members[0].u.turn.ap_change = 0;
                    return 0;
                }
                if ((*(u32*)g_Game.members & 0xFFFF00) == 0x200) {
                    goto set_pending;
                }
            }
            if ((g_Battle.turn_cursor == 6) && ((*(u32*)g_Game.members & 0xFFFF00) == 0x200)) {
            set_pending:
                g_Battle.state |= BATTLE_STATE_REPRISAL_PENDING;
                return 0;
            }
            return 0;
        case BOSS_EVENT_RESTART_BEGIN:
            D_801463D0 = (g_Battle.turn_cursor >> 1) + 1;
            if (g_Battle.turn_cursor == 1) {
                g_MenuPanelMode = 2;
                Message_StartAreaMessage(0x1B);
                return 0;
            }
            if (g_Battle.turn_cursor == 2) {
                g_MenuPanelMode                       = 2;
                g_Game.members[0].u.turn.command.type = BATTLE_ACTION_ATTACK;
                Message_StartAreaMessage(0x1C);
                return 0;
            }
            if (g_Battle.turn_cursor == 3) {
                g_MenuPanelMode = 2;
                Message_StartAreaMessage(0x1D);
                return 0;
            }
            if ((g_Battle.turn_cursor == 4) && !(g_Battle.state & BATTLE_STATE_REPRISAL_PENDING)) {
                g_Game.members[0].u.turn.command.type = BATTLE_ACTION_ABILITY;
                g_Game.members[0].u.turn.command.id   = 0x46;
                return 0;
            }
            if (D_80146322 == 5) {
                g_MenuPanelMode = 2;
                Message_StartAreaMessage(0x1E);
                return 0;
            }
            if (D_80146322 == 6) {
                if (!(g_Battle.state & BATTLE_STATE_REPRISAL_PENDING)) {
                    g_MenuPanelMode = 2;
                    Message_StartAreaMessage(0x1F);
                    g_Game.members[0].u.turn.command.type       = BATTLE_ACTION_ATTACK;
                    g_Game.members[0].chr.stats.critical_chance = 100;
                    g_BattleEnemyBattlers[0].hp                 = 1;
                }
                return 0;
            }
            return 0;
        case BOSS_EVENT_ACTION_START:
        case BOSS_EVENT_TURN_END:
        case BOSS_EVENT_EFFECTS_LOADED:
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}
#else
INCLUDE_ASM(func_800C2208);
#endif
