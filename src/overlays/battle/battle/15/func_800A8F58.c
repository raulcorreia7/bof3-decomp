#include "battle_15.h"

/* Rolls the death touch of weapons 0x1B, 0x3F and 0x44: each unblocked target with death resistance under 6
 * gets damage flag 0x100 at 1 in 12; returns whether any target did. */
MATCH s32 func_800A8F58(void) {
    s32 count;
    u8  i;
    s32 weapon;

    count  = 0;
    weapon = g_Game.current->chr.equip.weapon;
    if (weapon != 0x3F) {
        if (weapon < 0x40) {
            if (weapon != 0x1B) {
                return 0;
            }
        } else if (weapon != 0x44) {
            return 0;
        }
    }
    if (g_Battle.target_selector & BATTLE_TARGET_BOTH_SIDES) {
        if (g_Battle.target_selector & BATTLE_TARGET_PARTY_SIDE) {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                    if (g_Game.members[i].chr.stats.resistances[RES_INDEX_DEATH] < 6) {
                        if ((rand() % 12) == 0) {
                            count += 1;
                            g_Game.members[i].u.turn.damage_flags.value |= 0x100;
                        }
                    }
                }
            }
        } else {
            for (i = 3; i < 11; i++) {
                if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                    if (ENEMY_COMBATANT(i).stats.resistances[RES_INDEX_DEATH] < 6) {
                        if ((rand() % 12) == 0) {
                            count += 1;
                            ENEMY_COMBATANT(i).turn.damage_flags.value |= 0x100;
                        }
                    }
                }
            }
        }
        if ((u8)count != 0) {
            return 1;
        }
    } else if (g_Battle.target_selector < 3) {
        if (!(Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK) && (g_Game.members[g_Battle.target_selector].chr.stats.resistances[RES_INDEX_DEATH] < 6)) {
            if ((rand() % 12) == 0) {
                g_Game.members[g_Battle.target_selector].u.turn.damage_flags.value |= 0x100;
                return 1;
            }
        }
    } else {
        if (!(Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK) && (ENEMY_COMBATANT(g_Battle.target_selector).stats.resistances[RES_INDEX_DEATH] < 6)) {
            if ((rand() % 12) == 0) {
                ENEMY_COMBATANT(g_Battle.target_selector).turn.damage_flags.value |= 0x100;
                return 1;
            }
        }
    }
    return 0;
}
