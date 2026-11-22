#include "battle_15.h"

#ifdef NON_MATCHING
/* Commits a party battler's queued command: retargets when the battler cannot act on it, then
 * fills g_Battle.action_type and g_Battle.target_selector for the action handler. */
NON_MATCHING void func_800AB0B8(s32 battler) {
    PartyMember* member;
    u8           slot;
    u8           target;
    u8           type;

    slot                 = battler & 0xFF;
    member               = &g_Game.members[slot];
    g_Battle.action_type = member->u.turn.command.type;
    if ((member->chr.status & STATUS_CONFUSED) || (member->u.turn.action_flags.value & (BATTLER_ACTION_CHARGING | BATTLER_ACTION_DRAGON_FORM_BERSERK)) ||
        (member->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED)) {
        if (func_800A9304(slot) != 0) {
            if ((member->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) == 0) {
                if ((rand() & 7) < 3 || g_Battle.living_party_count == 1) {
                    g_Battle.target_selector = Battle_TargetNext((rand() & 7) + 3);
                } else {
                    g_Battle.target_selector = func_800AB68C(slot);
                }
            } else {
                goto after_retarget;
            }
        }
        member->u.turn.command.type = BATTLE_COMMAND_ATTACK;
        g_Battle.action_type        = BATTLE_COMMAND_ATTACK;
        return;
    }
after_retarget:
    if (member->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) {
        func_800AB570(slot);
        return;
    }
    if (g_Battle.flags & BATTLE_STATE_COMMAND_ARMED) {
        func_801DD978();
        return;
    }
    target = member->u.turn.command.target;
    if (target & BATTLE_TARGET_BOTH_SIDES) {
        g_Battle.target_selector = target;
        return;
    }
    type = member->u.turn.command.type;
    if (type == BATTLE_COMMAND_ABILITY) {
        if (Battle_SlotIsBlocked(target) == 0) {
            g_Battle.target_selector = target;
            return;
        }
        if (func_800AB470(slot) != 0) {
            g_Battle.target_selector = target;
            return;
        }
        if (target >= BATTLE_PARTY_CHARACTERS_COUNT) {
            g_Battle.target_selector = Battle_TargetNext(target);
            return;
        }
        if (g_Abilities[member->u.turn.command.id].targeting_flags & ABILITY_TARGET_FLAG_OPPONENT) {
            func_801DD978();
            return;
        }
        if (g_Battle.living_party_count != 1) {
            g_Battle.target_selector = func_800AB68C(slot);
            return;
        }
        g_Battle.target_selector = slot;
        return;
    }
    if (type == BATTLE_COMMAND_ITEM) {
        if (Battle_SlotIsBlocked(target) == 0) {
            g_Battle.target_selector = target;
            return;
        }
        if (func_800AB4BC(slot) != 0) {
            g_Battle.target_selector = target;
            return;
        }
        if (target >= BATTLE_PARTY_CHARACTERS_COUNT) {
            g_Battle.target_selector = Battle_TargetNext(target);
            return;
        }
        if (Item_GetFlags(member->u.turn.command.id >> 8, member->u.turn.command.id & 0xFF) & ITEM_SHOW_NAME) {
            func_801DD978();
            return;
        }
        if (g_Battle.living_enemy_count != 1) {
            g_Battle.target_selector = Battle_PickRandomTarget(target);
            return;
        }
        g_Battle.target_selector = Battle_TargetNext(target);
        return;
    }
    if (type < BATTLE_COMMAND_DEFEND) {
        if (Battle_SlotIsBlocked(target) == 0) {
            g_Battle.target_selector = target;
        } else {
            func_801DD978();
        }
    }
}
#else
INCLUDE_ASM(func_800AB0B8);
#endif
