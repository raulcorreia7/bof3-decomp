#define GAME_SCRATCH_BASE_SCALAR
#include "battle_03.h"

/* computes one hit's damage: the element id defaults to the attacker's weapon,
 * then the weapon-vs-enemy-kind doubling, status reactions, the random spread and the
 * +/-9999 clamp.
 */
/* func_801DC044 */
MATCH s16 Battle_CalcDamage(u8 attacker_slot, u8 target_slot, u16 element_id) {
    DamageSpread spread;
    s16          damage;
    u16          status;
    u8           flags;
    u16*         power;

    spread = D_801D0C7C;
    if (element_id == BATTLE_ELEMENT_FROM_WEAPON) {
        if (BATTLER_IS_PLAYER(attacker_slot)) {
            *(u16*)D_1F800000 = g_Weapons[g_Game.members[attacker_slot].chr.equip.weapon].element;
        } else {
            *(u16*)D_1F800000 = 0;
        }
    } else {
        *(u16*)D_1F800000 = element_id;
    }
    if (BATTLER_IS_PLAYER(attacker_slot)) {
        if (g_Game.members[attacker_slot].u.turn.action_flags.value & COMBATANT_FLAG_POWER_BOOST) {
            power = &D_801EC30C;
            *power += (*power * g_Game.members[attacker_slot].focus_counter) >> 1;
            g_Game.members[attacker_slot].focus_counter = 0;
            g_Game.members[attacker_slot].u.turn.action_flags.value &= ~COMBATANT_FLAG_POWER_BOOST;
        }
    } else if (ENEMY_COMBATANT(attacker_slot).turn.action_flags.value & COMBATANT_FLAG_POWER_BOOST) {
        power                                  = &D_801EC30C;
        *power                                 = (*power * ENEMY_COMBATANT(attacker_slot).unk_114) >> 1;
        ENEMY_COMBATANT(attacker_slot).unk_114 = 0;
        ENEMY_COMBATANT(attacker_slot).turn.action_flags.value &= ~COMBATANT_FLAG_POWER_BOOST;
    }
    damage = Battle_RollBaseDamage(attacker_slot, target_slot, 0);
    if (BATTLER_IS_PLAYER(attacker_slot) && !BATTLER_IS_PLAYER(target_slot)) {
        if ((g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_DEMONSBANE || g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_HOLY_AVENGER ||
             g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_ARIES_SPEAR) &&
            ENEMY_COMBATANT(target_slot).enemy_id.byte.family == ENEMY_FAMILY_DEMON) {
            damage *= 2;
        }
        if ((g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_DRAGON_BLADE || g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_DRAGON_SPEAR ||
             g_Game.members[attacker_slot].chr.equip.weapon == WEAPON_DRAGONFANG) &&
            ENEMY_COMBATANT(target_slot).enemy_id.byte.family == ENEMY_FAMILY_DRAGON) {
            damage *= 2;
        }
    }
    if (BATTLER_IS_PLAYER(target_slot)) {
        status = g_Game.members[target_slot].chr.status;
        flags  = g_Game.members[target_slot].u.turn.damage_flags.value;
    } else {
        status = ENEMY_COMBATANT(target_slot).status;
        flags  = ENEMY_COMBATANT(target_slot).turn.damage_flags.value;
    }
    if (status & (STATUS_PARALYZED | STATUS_CONFUSED | STATUS_SLEEPING)) {
        if (status & STATUS_SLEEPING) {
            *(volatile s16*)&D_801463DA |= 0x40;
            if (BATTLER_IS_PLAYER(target_slot)) {
                func_800A36F0(g_Game.members[target_slot].slot, 0x40);
                g_Game.members[target_slot].u.turn.counter = 0;
            } else {
                func_800A36F0(ENEMY_COMBATANT(target_slot).slot, 0x40);
                ENEMY_COMBATANT(target_slot).turn.counter = 0;
            }
            if (damage == 0) {
                damage = 1;
            }
        }
        if (status & STATUS_CONFUSED) {
            *(volatile s16*)&D_801463DA |= 0x20;
            if (BATTLER_IS_PLAYER(target_slot)) {
                func_800A36F0(g_Game.members[target_slot].slot, 0x20);
                g_Game.members[target_slot].u.turn.counter = 0;
            } else {
                func_800A36F0(ENEMY_COMBATANT(target_slot).slot, 0x20);
                ENEMY_COMBATANT(target_slot).turn.counter = 0;
            }
            if (damage == 0) {
                damage = 1;
            }
        }
        if ((status & STATUS_PARALYZED) && damage == 0) {
            damage = 1;
        }
    } else if (BATTLER_IS_PLAYER(target_slot)) {
        damage = Battle_RollHitOnParty(damage, attacker_slot, target_slot);
    } else {
        damage = Battle_RollHitOnEnemy(damage, attacker_slot, target_slot);
    }
    if (flags & 0x2) {
        damage = (damage * spread.percent[RANDOM_MOD(8)]) / 100;
    }
    if (g_Battle.state & BATTLE_STATE_CRITICAL) {
        damage = damage * 2 + (s16)Battle_RollBaseDamage(attacker_slot, target_slot, 1) / 4;
    }
    if (BATTLER_IS_PLAYER(target_slot) && g_PartyFormation == 2) {
        damage -= damage >> 2;
    }
    if (status & STATUS_POISONED) {
        damage -= damage >> 2;
    }
    if ((status & (STATUS_CONFUSED | STATUS_SLEEPING)) && damage == 0) {
        damage = 1;
    }
    if ((g_Battle.state & BATTLE_STATE_CRITICAL) && damage == 0) {
        damage = 1;
    }
    if (BATTLER_IS_PLAYER(target_slot)) {
        if (g_Game.members[target_slot].u.turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
            damage = 0;
        }
    } else if (ENEMY_COMBATANT(target_slot).turn.damage_flags.value & COMBATANT_FLAG_DAMAGE_IMMUNE) {
        damage = 0;
    }
    if (damage >= 10000) {
        damage = 9999;
    }
    CLAMP_MIN(damage, -9999);
    return damage;
}
