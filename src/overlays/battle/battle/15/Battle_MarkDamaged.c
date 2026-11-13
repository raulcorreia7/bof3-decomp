#include "battle_15.h"

/* marks battlers as damaged: bit 0x80 of the target_mask loops over
 * the three player rows, bit 0x40 over the eleven enemy rows, and a target_mask
 * without bits 0xC0 marks only the one indexed battler.
 */
/* func_800A9820 */
MATCH void Battle_MarkDamaged(u8 target_mask) {
    s32 i;
    u8  index;

    if (target_mask & 0xC0) {
        if (target_mask & 0x80) {
            for (i = 0; (u32)(i & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                index = i & BYTE_MASK;
                if ((Battle_SlotIsBlocked(index) & BYTE_MASK) == 0) {
                    g_Game.members[index].u.turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
                }
            }
        }
        if (target_mask & 0x40) {
            for (i = 3; (u32)(i & BYTE_MASK) < COMBATANT_COUNT; i++) {
                index = i & BYTE_MASK;
                if ((Battle_SlotIsBlocked(index) & BYTE_MASK) == 0) {
                    ENEMY_COMBATANT(index).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
                }
            }
        }
    } else {
        index = target_mask & BYTE_MASK;
        if (index < 3U) {
            g_Game.members[index].u.turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
            return;
        }
        ENEMY_COMBATANT(index).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
    }
}
