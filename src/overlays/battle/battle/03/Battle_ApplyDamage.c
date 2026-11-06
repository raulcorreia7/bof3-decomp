#include "battle_03.h"

/* func_801DBB78 */
MATCH u32 Battle_ApplyDamage(u8 attacker, u8 target) {
    s32 damage;

    if (BATTLER_IS_PLAYER(target)) {
        g_BattlePartyBattlers[target].turn.target_flags = 0x11;
    } else {
        ENEMY_COMBATANT(target).turn.target_flags = 0x11;
    }
    damage = Battle_CalcDamage(attacker, target, 0xFFFF);
    if (BATTLER_IS_PLAYER(target)) {
        if (g_BattlePartyBattlers[target].turn.damage_flags.value & COMBATANT_FLAG_HURT_REACTION) {
            damage = g_BattlePartyBattlers[target].chr.hp;
            func_801DE560(1, 0, 0, 0x1E, D_801EB075);
            g_BattleMessageState = 1;
            g_BattlePartyBattlers[target].turn.damage_flags.value &= ~0x100;
        }
        if (damage > 0) {
            if (damage < g_BattlePartyBattlers[target].chr.hp) {
                g_BattlePartyBattlers[target].chr.hp -= damage;
            } else {
                if (damage - g_BattlePartyBattlers[target].chr.hp < g_BattlePartyBattlers[target].chr.willpower) {
                    if (!(g_BattlePartyBattlers[target].turn.action_flags.value & 1) &&
                        !(g_BattlePartyBattlers[target].turn.action_flags.value & 2)) {
                        g_BattlePartyBattlers[target].turn.damage_flags.value |= 4;
                    }
                }
                g_BattlePartyBattlers[target].chr.hp = 0;
            }
        } else if (g_BattlePartyBattlers[target].chr.hp - damage < g_BattlePartyBattlers[target].chr.stats.max_hp) {
            g_BattlePartyBattlers[target].chr.hp -= damage;
        } else {
            g_BattlePartyBattlers[target].chr.hp = g_BattlePartyBattlers[target].chr.stats.max_hp;
            g_BattlePartyBattlers[target].turn.target_flags |= 4;
        }
    } else if (ENEMY_COMBATANT(target).hp != 0xFFFF) {
        if ((ENEMY_COMBATANT(target).turn.damage_flags.value & COMBATANT_FLAG_HURT_REACTION) &&
            ENEMY_COMBATANT(target).hp <= 0x7FFF) {
            damage = ENEMY_COMBATANT(target).hp;
            func_801DE560(1, 0, 0, 0x1E, D_801EB075);
            g_BattleMessageState = 1;
            ENEMY_COMBATANT(target).turn.damage_flags.value &= ~0x100;
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
            ENEMY_COMBATANT(target).turn.target_flags |= 4;
        }
    }
    if (attacker < 3 && g_BattlePartyBattlers[attacker].unk_13A[2] == 5 && damage != 0) {
        if (g_BattlePartyBattlers[attacker].chr.equip.weapon == WEAPON_SLEEP_SHELLS &&
            !func_800A3DF8(attacker, target)) {
            func_800A31E0(target, 0x40);
        }
        if (g_BattlePartyBattlers[attacker].chr.equip.weapon == WEAPON_FLASH_SHELLS &&
            !func_800A3DF8(attacker, target)) {
            func_800A31E0(target, 8);
        }
        if (g_BattlePartyBattlers[attacker].chr.equip.weapon == WEAPON_GAS_SHELLS && !func_800A3DF8(attacker, target)) {
            func_800A31E0(target, 0x20);
        }
    }
    return (s16)damage;
}
