#include "battle_15.h"

#ifdef NON_MATCHING
/* Commits a party battler's queued command: retargets when the battler cannot act on it, then
 * fills g_Battle.action_type and g_Battle.target_selector for the action handler. */
NON_MATCHING void func_800AB0B8(s32 battler) {
    BattleTurn* turn;
    u8          target;

    turn                 = &g_Game.members[(u8)battler].u.turn;
    g_Battle.action_type = turn->command.type;
    if ((g_Game.members[(u8)battler].chr.status & STATUS_CONFUSED) || (g_Game.members[(u8)battler].u.turn.action_flags.value & (BATTLER_ACTION_CHARGING | BATTLER_ACTION_DRAGON_FORM_BERSERK)) ||
        (g_Game.members[(u8)battler].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED)) {
        if (func_800A9304((u8)battler) != 0) {
            if (g_Game.members[(u8)battler].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) {
                goto after_retarget;
            }
            if ((rand() & 7) >= 3 && g_Battle.living_party_count != 1) {
                g_Battle.target_selector = func_800AB68C((u8)battler);
            } else {
                g_Battle.target_selector = Battle_TargetNext((rand() & 7) + 3);
            }
        }
        turn->command.type   = BATTLE_COMMAND_ATTACK;
        g_Battle.action_type = BATTLE_COMMAND_ATTACK;
        return;
    }
after_retarget:
    if (turn->action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) {
        func_800AB570((u8)battler);
        return;
    }
    if (g_Battle.flags & BATTLE_STATE_COMMAND_ARMED) {
        func_801DD978();
        return;
    }
    target = turn->command.target;
    if (target & BATTLE_TARGET_BOTH_SIDES) {
        g_Battle.target_selector = target;
        return;
    }
    switch (turn->command.type) {
        case 0:
        case BATTLE_COMMAND_ATTACK:
            battler = target;
            if (Battle_SlotIsBlocked(battler) == 0) {
                g_Battle.target_selector = battler;
                return;
            }
            func_801DD978();
            return;
        case BATTLE_COMMAND_ABILITY:
            if (Battle_SlotIsBlocked(target) == 0) {
                break;
            }
            if ((u8)func_800AB470((u8)battler) != 0) {
                break;
            }
            if (turn->command.target < BATTLE_PARTY_CHARACTERS_COUNT) {
                if (g_Abilities[turn->command.id].targeting_flags & ABILITY_TARGET_FLAG_OPPONENT) {
                    func_801DD978();
                    return;
                }
                if (g_Battle.living_party_count == 1) {
                    g_Battle.target_selector = battler;
                    return;
                }
                g_Battle.target_selector = func_800AB68C((u8)battler);
            } else {
                g_Battle.target_selector = Battle_TargetNext(turn->command.target);
            }
            return;
        case BATTLE_COMMAND_ITEM:
            if (Battle_SlotIsBlocked(target) == 0) {
                break;
            }
            if ((u8)func_800AB4BC((u8)battler) != 0) {
                break;
            }
            if (turn->command.target < BATTLE_PARTY_CHARACTERS_COUNT) {
                if (Item_GetFlags(turn->command.id >> 8, turn->command.id & 0xFF) & ITEM_SHOW_NAME) {
                    func_801DD978();
                    return;
                }
                if (turn->command.target < BATTLE_PARTY_CHARACTERS_COUNT) {
                    if (g_Battle.living_party_count != 1) {
                        g_Battle.target_selector = func_800AB68C((u8)battler);
                    } else {
                        g_Battle.target_selector = battler;
                    }
                } else if (g_Battle.living_enemy_count != 1) {
                    g_Battle.target_selector = func_800AB760(turn->command.target);
                } else {
                    g_Battle.target_selector = Battle_TargetNext(turn->command.target);
                }
            } else {
                g_Battle.target_selector = Battle_TargetNext(turn->command.target);
            }
            return;
        default:
            return;
    }
    g_Battle.target_selector = turn->command.target;
}
#else
INCLUDE_ASM(func_800AB0B8);
#endif
