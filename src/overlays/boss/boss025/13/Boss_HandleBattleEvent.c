#include "boss025_13.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    u8 damage_flags;
    u8 battler;

    switch (mode & BYTE_MASK) {
        case BOSS_EVENT_RESTART_BEGIN:
            if (g_BattleEnemyBattlers[0].status & STATUS_KO) {
                g_Battle.outcome.result |= 4;
                g_Battle.boss_flags |= 1;
            } else if (g_BattleEnemyBattlers[1].status & STATUS_KO) {
                g_Battle.outcome.result |= 4;
                g_Battle.boss_flags |= 2;
            } else {
                if (g_Battle.outcome.result == 0 && !(g_Battle.boss_flags & 8)) {
                    battler = g_Battle.turn_order[g_Battle.turn_cursor - 1];
                    if (BATTLER_IS_PLAYER(battler)) {
                        damage_flags = g_Game.members[battler].u.turn.damage_flags.value;
                        if (!(damage_flags & COMBATANT_FLAG_COMMAND_ENTERED)) {
                            if (!(damage_flags & COMBATANT_FLAG_DEFENDING)) {
                                g_Battle.outcome.result |= 4;
                                g_Battle.boss_flags |= 4;
                            }
                        }
                    }
                }
                if (g_Battle.boss_flags & 0x20) {
                    g_Battle.boss_flags &= 0xD7;
                }
            }
            break;
        case BOSS_EVENT_TURN_END:
            if (!(g_Battle.outcome.result & 4) && (g_Battle.boss_flags & 0x10)) {
                g_Battle.boss_flags &= 0xEF;
                SP_REF(PartyMember*, 0x44u) = (PartyMember*)D_801EB748;
                Actor_RequestScript(0xC);
                g_Battle.boss_flags |= 8;
            }
            break;
        case BOSS_EVENT_ACTION_START:
        case BOSS_EVENT_TICK:
        case BOSS_EVENT_EFFECTS_LOADED:
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}
