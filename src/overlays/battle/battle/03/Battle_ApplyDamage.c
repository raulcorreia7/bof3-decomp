#include "battle_03.h"

/* func_801DBB78 */
MATCH u32 Battle_ApplyDamage(u8 attacker, u8 target) {
    s32 damage;

    if (BATTLER_IS_PLAYER(target)) {
        g_Game.members[target].u.turn.target_flags = 0x11;
    } else {
        ENEMY_COMBATANT(target).turn.target_flags = 0x11;
    }
    damage = Battle_CalcDamage(attacker, target, BATTLE_ELEMENT_FROM_WEAPON);
    if (BATTLER_IS_PLAYER(target)) {
        if (g_Game.members[target].u.turn.damage_flags.value & COMBATANT_FLAG_HURT_REACTION) {
            damage = g_Game.members[target].chr.hp;
            Battle_QueueEvent(1, 0, 0, 30, D_801EB075);
            g_BattleMessageState = 1;
            g_Game.members[target].u.turn.damage_flags.value &= ~COMBATANT_FLAG_HURT_REACTION;
        }
        if (damage > 0) {
            if (damage < g_Game.members[target].chr.hp) {
                g_Game.members[target].chr.hp -= damage;
            } else {
                if (damage - g_Game.members[target].chr.hp < g_Game.members[target].chr.willpower) {
                    if (!(g_Game.members[target].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) && !(g_Game.members[target].u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM)) {
                        g_Game.members[target].u.turn.damage_flags.value |= COMBATANT_FLAG_WILLPOWER_SURVIVED;
                    }
                }
                g_Game.members[target].chr.hp = 0;
            }
        } else if (g_Game.members[target].chr.hp - damage < g_Game.members[target].chr.stats.max_hp) {
            g_Game.members[target].chr.hp -= damage;
        } else {
            g_Game.members[target].chr.hp = g_Game.members[target].chr.stats.max_hp;
            g_Game.members[target].u.turn.target_flags |= BATTLE_HIT_HP_MAX;
        }
    } else if (ENEMY_COMBATANT(target).hp != 65535) {
        if ((ENEMY_COMBATANT(target).turn.damage_flags.value & COMBATANT_FLAG_HURT_REACTION) && ENEMY_COMBATANT(target).hp <= 32767) {
            damage = ENEMY_COMBATANT(target).hp;
            Battle_QueueEvent(1, 0, 0, 30, D_801EB075);
            g_BattleMessageState = 1;
            ENEMY_COMBATANT(target).turn.damage_flags.value &= ~COMBATANT_FLAG_HURT_REACTION;
        }
        if (damage > 0) {
            if (damage < ENEMY_COMBATANT(target).hp) {
                ENEMY_COMBATANT(target).hp -= damage;
            } else {
                ENEMY_COMBATANT(target).hp = 0;
            }
        } else if (ENEMY_COMBATANT(target).hp - damage < ENEMY_COMBATANT(target).stats.max_hp) {
            ENEMY_COMBATANT(target).hp -= damage;
        } else {
            ENEMY_COMBATANT(target).hp = ENEMY_COMBATANT(target).stats.max_hp;
            ENEMY_COMBATANT(target).turn.target_flags |= BATTLE_HIT_HP_MAX;
        }
    }
    if (attacker < 3 && g_Game.members[attacker].unk_13A[2] == 5 && damage != 0) {
        if (g_Game.members[attacker].chr.equip.weapon == WEAPON_SLEEP_SHELLS && !func_800A3DF8(attacker, target)) {
            func_800A31E0(target, 0x40);
        }
        if (g_Game.members[attacker].chr.equip.weapon == WEAPON_FLASH_SHELLS && !func_800A3DF8(attacker, target)) {
            func_800A31E0(target, 8);
        }
        if (g_Game.members[attacker].chr.equip.weapon == WEAPON_GAS_SHELLS && !func_800A3DF8(attacker, target)) {
            func_800A31E0(target, 0x20);
        }
    }
    return (s16)damage;
}
