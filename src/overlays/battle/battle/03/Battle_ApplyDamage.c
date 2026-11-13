#include "battle_03.h"

/* func_801DBB78 */
MATCH u32 Battle_ApplyDamage(u8 attacker_slot, u8 target_slot) {
    s32 damage;

    if (BATTLER_IS_PLAYER(target_slot)) {
        g_Game.members[target_slot].u.turn.target_flags = 0x11;
    } else {
        ENEMY_COMBATANT(target_slot).turn.target_flags = 0x11;
    }
    damage = Battle_CalcDamage(attacker_slot, target_slot, BATTLE_ELEMENT_FROM_WEAPON);
    if (BATTLER_IS_PLAYER(target_slot)) {
        if (g_Game.members[target_slot].u.turn.damage_flags.value & COMBATANT_FLAG_HURT_REACTION) {
            damage = g_Game.members[target_slot].chr.hp;
            func_801DE560(1, 0, 0, 30, D_801EB075);
            g_BattleMessageState = 1;
            g_Game.members[target_slot].u.turn.damage_flags.value &= ~COMBATANT_FLAG_HURT_REACTION;
        }
        if (damage > 0) {
            if (damage < g_Game.members[target_slot].chr.hp) {
                g_Game.members[target_slot].chr.hp -= damage;
            } else {
                if (damage - g_Game.members[target_slot].chr.hp < g_Game.members[target_slot].chr.willpower) {
                    if (!(g_Game.members[target_slot].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) &&
                        !(g_Game.members[target_slot].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM)) {
                        g_Game.members[target_slot].u.turn.damage_flags.value |= COMBATANT_FLAG_WILLPOWER_SURVIVED;
                    }
                }
                g_Game.members[target_slot].chr.hp = 0;
            }
        } else if (g_Game.members[target_slot].chr.hp - damage < g_Game.members[target_slot].chr.stats.max_hp) {
            g_Game.members[target_slot].chr.hp -= damage;
        } else {
            g_Game.members[target_slot].chr.hp = g_Game.members[target_slot].chr.stats.max_hp;
            g_Game.members[target_slot].u.turn.target_flags |= BATTLE_HIT_HP_MAX;
        }
    } else if (ENEMY_COMBATANT(target_slot).hp != 65535) {
        if ((ENEMY_COMBATANT(target_slot).turn.damage_flags.value & COMBATANT_FLAG_HURT_REACTION) && ENEMY_COMBATANT(target_slot).hp <= 32767) {
            damage = ENEMY_COMBATANT(target_slot).hp;
            func_801DE560(1, 0, 0, 30, D_801EB075);
            g_BattleMessageState = 1;
            ENEMY_COMBATANT(target_slot).turn.damage_flags.value &= ~COMBATANT_FLAG_HURT_REACTION;
        }
        if (damage > 0) {
            if (damage < ENEMY_COMBATANT(target_slot).hp) {
                ENEMY_COMBATANT(target_slot).hp -= damage;
            } else {
                ENEMY_COMBATANT(target_slot).hp = 0;
            }
        } else if (ENEMY_COMBATANT(target_slot).hp - damage < ENEMY_COMBATANT(target_slot).stats.max_hp) {
            ENEMY_COMBATANT(target_slot).hp -= damage;
        } else {
            ENEMY_COMBATANT(target_slot).hp = ENEMY_COMBATANT(target_slot).stats.max_hp;
            ENEMY_COMBATANT(target_slot).turn.target_flags |= BATTLE_HIT_HP_MAX;
        }
    }
    if (attacker_slot < 3 && g_Game.members[attacker_slot].unk_13A[2] == 5 && damage != 0) {
        if (g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_SLEEP_SHELLS && !func_800A3DF8(attacker_slot, target_slot)) {
            func_800A31E0(target_slot, 0x40);
        }
        if (g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_FLASH_SHELLS && !func_800A3DF8(attacker_slot, target_slot)) {
            func_800A31E0(target_slot, 8);
        }
        if (g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_GAS_SHELLS && !func_800A3DF8(attacker_slot, target_slot)) {
            func_800A31E0(target_slot, 0x20);
        }
    }
    return (s16)damage;
}
