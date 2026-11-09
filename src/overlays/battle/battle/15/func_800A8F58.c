#include "battle_15.h"

/* Rolls the battler's hurt reaction: when the command state is a hit state, gives each live battler a 1-in-12
 * chance per frame to raise its 0x100 reaction flag. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_800A8F58(void) {
    u32 off;
    s32 count;
    s32 roll;
    u32 i;
    u8  kind;

    kind = FIELD(u8, g_Game.current, 0x82u);
    if (kind != 0x3F) {
        if (kind < 0x40) {
            if (kind != 0x1B) {
                return 0;
            }
        } else if (kind != 0x44) {
            return 0;
        }
    }
    count = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_BOTH_SIDES) {
        if (g_Battle.target_selector & BATTLE_TARGET_PARTY_SIDE) {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                    off = i * BATTLE_PARTY_STRIDE;
                    if (g_Game.members[i].chr.stats.resistances[RES_INDEX_DEATH] < 6) {
                        roll = rand();
                        if (roll == (roll / 12) * 12) {
                            count += 1;
                            FIELD(u32, D_80145FB4, off) |= 0x100;
                        }
                    }
                }
            }
        } else {
            for (i = 3; i < 11; i++) {
                if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                    if (ENEMY_COMBATANT(i).stats.resistances[RES_INDEX_DEATH] < 6) {
                        roll = rand();
                        if (roll == (roll / 12) * 12) {
                            count += 1;
                            ENEMY_COMBATANT(i).turn.damage_flags.value |= 0x100;
                        }
                    }
                }
            }
        }
        if (count != 0) {
            return 1;
        }
        return 0;
    }
    if (g_Battle.target_selector < 3) {
        if (!(Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK) &&
            (g_Game.members[g_Battle.target_selector].chr.stats.resistances[RES_INDEX_DEATH] < 6)) {
            roll = rand();
            if (roll == (roll / 12) * 12) {
                FIELD(u32, D_80145FB4, g_Battle.target_selector * BATTLE_PARTY_STRIDE) |= 0x100;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    if (!(Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK) &&
        (ENEMY_COMBATANT(g_Battle.target_selector).stats.resistances[RES_INDEX_DEATH] < 6)) {
        roll = rand();
        if (roll == (roll / 12) * 12) {
            ENEMY_COMBATANT(g_Battle.target_selector).turn.damage_flags.value |= 0x100;
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM(func_800A8F58);
#endif
