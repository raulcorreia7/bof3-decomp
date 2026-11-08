#include "battle_15.h"

/* Rolls the battler's hurt reaction: when the command state is a hit state, gives each live battler a 1-in-12
 * chance per frame to raise its 0x100 reaction flag. */
/* nonmatching unmeasured: tried opcode@+0x8: the hit-state gate and the 1-in-12 roll chain differ; the slot loops and
 * flag stores are in place (first-draft pointer-counter code was uncompilable). resume: rebuild the
 * g_BattleTargetSelector mask gate and the rand()/12 roll from the asm. */
#ifdef NON_MATCHING
NON_MATCHING s32 func_800A8F58(void) {
    u32 off;
    s32 count;
    s32 roll;
    u32 i;
    u8  kind;

    kind = FIELD(u8, g_GameState, 0x82u);
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
    if (g_BattleTargetSelector & BATTLE_TARGET_BOTH_SIDES) {
        if (g_BattleTargetSelector & BATTLE_TARGET_PARTY_SIDE) {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                    off = i * BATTLE_PARTY_STRIDE;
                    if (g_BattlePartyBattlers[i].chr.stats.resistances[RES_INDEX_DEATH] < 6) {
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
    if (g_BattleTargetSelector < 3) {
        if (!(Battle_SlotIsBlocked(g_BattleTargetSelector) & BYTE_MASK) &&
            (g_BattlePartyBattlers[g_BattleTargetSelector].chr.stats.resistances[RES_INDEX_DEATH] < 6)) {
            roll = rand();
            if (roll == (roll / 12) * 12) {
                FIELD(u32, D_80145FB4, g_BattleTargetSelector * BATTLE_PARTY_STRIDE) |= 0x100;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    if (!(Battle_SlotIsBlocked(g_BattleTargetSelector) & BYTE_MASK) &&
        (ENEMY_COMBATANT(g_BattleTargetSelector).stats.resistances[RES_INDEX_DEATH] < 6)) {
        roll = rand();
        if (roll == (roll / 12) * 12) {
            ENEMY_COMBATANT(g_BattleTargetSelector).turn.damage_flags.value |= 0x100;
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM(func_800A8F58);
#endif
