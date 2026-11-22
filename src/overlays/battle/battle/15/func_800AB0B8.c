#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800AB0B8(u32 index) {
    PartyMember* battler;
    BattleTurn*  turn;
    u8           target;
    u8           result;

    battler              = &g_Game.members[index & BYTE_MASK];
    turn                 = &battler->u.turn;
    g_Battle.action_type = turn->command.type;
    if ((battler->chr.status & STATUS_CONFUSED) != 0 || (turn->action_flags.value & (BATTLER_ACTION_CHARGING | BATTLER_ACTION_DRAGON_FORM_BERSERK)) != 0 ||
        (turn->action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) != 0) {
        if ((func_800A9304(index & BYTE_MASK) & BYTE_MASK) != 0) {
            if ((turn->action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) != 0) {
                goto choose_target;
            }
            if ((rand() & 7) < 3 || g_Battle.living_party_count == 1) {
                result = Battle_TargetNext((rand() & 7) + 3);
            } else {
                result = func_800AB68C(index & BYTE_MASK);
            }
            g_Battle.target_selector = result;
        }
        turn->command.type   = BATTLE_COMMAND_ATTACK;
        g_Battle.action_type = BATTLE_ACTION_ATTACK;
        return;
    }

choose_target:
    if ((turn->action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) != 0) {
        func_800AB570(index & BYTE_MASK);
        return;
    }
    if ((g_Battle.flags & BATTLE_STATE_COMMAND_ARMED) != 0) {
        goto retarget_default;
    }
    target = turn->command.target;
    if ((target & 0xC0) != 0) {
        g_Battle.target_selector = target;
        return;
    }
    switch (turn->command.type) {
        case BATTLE_COMMAND_EXAMINE:
        case BATTLE_COMMAND_ATTACK:
        case BATTLE_COMMAND_DEFEND:
        case BATTLE_COMMAND_ESCAPE:
            if ((Battle_SlotIsBlocked(target) & BYTE_MASK) == 0) {
                g_Battle.target_selector = target;
                return;
            }
            goto retarget_default;
        case BATTLE_COMMAND_ABILITY:
            if ((Battle_SlotIsBlocked(target) & BYTE_MASK) == 0) {
                goto keep_target;
            }
            if ((func_800AB470(index & BYTE_MASK) & BYTE_MASK) != 0) {
                goto keep_target;
            }
            if (target >= BATTLE_PARTY_CHARACTERS_COUNT) {
                result = Battle_TargetNext(target);
                goto store_result;
            }
            if ((g_Abilities[turn->command.id].targeting_flags & ABILITY_TARGET_FLAG_OPPONENT) != 0) {
                goto retarget_default;
            }
            if (g_Battle.living_party_count == 1) {
                g_Battle.target_selector = index;
                return;
            }
            result = func_800AB68C(index & BYTE_MASK);
            goto store_result;
        case BATTLE_COMMAND_ITEM:
            if ((Battle_SlotIsBlocked(target) & BYTE_MASK) == 0) {
                goto keep_target;
            }
            if ((func_800AB4BC(index & BYTE_MASK) & BYTE_MASK) != 0) {
                goto keep_target;
            }
            if (target >= BATTLE_PARTY_CHARACTERS_COUNT) {
                result = Battle_TargetNext(target);
                goto store_result;
            }
            if ((Item_GetFlags(turn->command.id >> 8, turn->command.id & BYTE_MASK) & ITEM_SHOW_NAME) != 0) {
                goto retarget_default;
            }
            if (turn->command.target < BATTLE_PARTY_CHARACTERS_COUNT) {
                if (g_Battle.living_party_count == 1) {
                    g_Battle.target_selector = index;
                    return;
                }
                result = func_800AB68C(index & BYTE_MASK);
            } else {
                if (g_Battle.living_enemy_count == 1) {
                    result = Battle_TargetNext(target);
                } else {
                    result = Battle_PickRandomTarget(target);
                }
            }
            goto store_result;
        default:
            return;
    }

retarget_default:
    func_801DD978();
    return;
keep_target:
    g_Battle.target_selector = target;
    return;
store_result:
    g_Battle.target_selector = result;
}
#else
INCLUDE_ASM(func_800AB0B8);
#endif
