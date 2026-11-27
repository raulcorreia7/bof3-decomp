#include "boss025_13.h"

MATCH u8 func_800C2208(u32 mode) {
    switch (mode & BYTE_MASK) {
        case BOSS_EVENT_TICK:
            if (!(g_Battle.boss_flags & 0x20) && g_Battle.phase.mode == 1) {
                Battle_AllocEffect(0, 8);
                g_Battle.boss_flags |= 0x20;
            }
            if (!(g_Battle.boss_flags & 0x10) && LOHU(g_Battle.phase) == 3) {
                g_Game.members[0].u.turn.command.type       = BATTLE_COMMAND_ATTACK;
                g_Game.members[0].chr.stats.accuracy        = 100;
                g_Game.members[0].chr.stats.critical_chance = 0;
                g_Game.members[0].u.turn.command.target     = 3;
                D_801EB724                                  = 0;
                D_801EB725                                  = 2;
                g_Battle.turn_order[0]                      = 0;
                g_Battle.turn_order[1]                      = 3;
                g_Battle.turn_order[2]                      = 0;
                g_Battle.turn_order[3]                      = 3;
                g_Battle.turn_order[4]                      = 0;
                g_Battle.turn_order[5]                      = 3;
                g_Battle.turn_order[6]                      = 0;
                g_Battle.turn_count                         = 7;
                D_801EB730 |= 2;
                g_Battle.boss_flags |= 0x10;
            }
            if (!(g_Battle.boss_flags & 1)) {
                g_UIPanelMode = 2;
                UI_MessageStartArea(MSG_BOSS025_025);
                g_Battle.boss_flags |= 1;
            } else if (!(g_Battle.boss_flags & 2)) {
                g_Self = (PartyMember*)g_BattleEnemyBattlers;
                Battle_RequestEnemyScript(8);
                g_Battle.boss_flags |= 2;
            } else if ((D_801462EC & 0x600) == 0x200) {
                g_UIPanelMode = 2;
                UI_MessageStartArea(MSG_BOSS025_026);
                g_Battle.boss_flags |= 4;
            } else {
                if (g_Battle.turn_cursor == 4) {
                    if ((LOW(g_Game) & 0xFFFF00) == 0x10600) {
                        g_Game.members[0].u.turn.hp_change = 0;
                        g_Game.members[0].u.turn.ap_change = 0;
                        g_Battle.action_type               = 0xFF;
                        break;
                    }
                    if ((LOW(g_Game) & 0xFFFF00) == 0x200) {
                        goto set_flag;
                    }
                }
                if (g_Battle.turn_cursor == 6 && (LOW(g_Game) & 0xFFFF00) == 0x200) {
                set_flag:
                    D_801462E8 |= 0x40;
                }
                break;
            }
            break;
        case BOSS_EVENT_RESTART_BEGIN:
            D_801463D0 = (g_Battle.turn_cursor >> 1) + 1;
            if (g_Battle.turn_cursor == 1) {
                g_UIPanelMode = 2;
                UI_MessageStartArea(MSG_BOSS025_027);
            } else if (g_Battle.turn_cursor == 2) {
                g_UIPanelMode                         = 2;
                g_Game.members[0].u.turn.command.type = BATTLE_COMMAND_ATTACK;
                UI_MessageStartArea(MSG_BOSS025_028);
            } else if (g_Battle.turn_cursor == 3) {
                g_UIPanelMode = 2;
                UI_MessageStartArea(MSG_BOSS025_029);
            } else if (g_Battle.turn_cursor == 4 && !(g_Battle.flags & 0x40)) {
                g_Game.members[0].u.turn.command.type = BATTLE_COMMAND_ABILITY;
                g_Game.members[0].u.turn.command.id   = 0x46;
            } else if (g_Battle.turn_cursor == 5) {
                g_UIPanelMode = 2;
                UI_MessageStartArea(MSG_BOSS025_030);
            } else if (g_Battle.turn_cursor == 6 && !(g_Battle.flags & 0x40)) {
                g_UIPanelMode = 2;
                UI_MessageStartArea(MSG_BOSS025_031);
                g_Game.members[0].u.turn.command.type       = BATTLE_COMMAND_ATTACK;
                g_Game.members[0].chr.stats.critical_chance = 100;
                D_801EB6C4                                  = 1;
            }
            break;
        case BOSS_EVENT_ACTION_START:
        case BOSS_EVENT_TURN_END:
        case BOSS_EVENT_EFFECTS_LOADED:
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}
