#include "battle_15.h"

/* marks battlers as damaged. */
MATCH void func_800A9820(u8 selector) {
    s32 i;
    u8  index;

    if (selector & 0xC0) {
        if (selector & 0x80) {
            for (i = 0; (u32)(i & BYTE_MASK) < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                index = i & BYTE_MASK;
                if ((Battle_SlotIsBlocked(index) & BYTE_MASK) == 0) {
                    g_Game.members[index].u.turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
                }
            }
        }
        if (selector & 0x40) {
            for (i = 3; (u32)(i & BYTE_MASK) < COMBATANT_COUNT; i++) {
                index = i & BYTE_MASK;
                if ((Battle_SlotIsBlocked(index) & BYTE_MASK) == 0) {
                    ENEMY_COMBATANT(index).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
                }
            }
        }
    } else {
        index = selector & BYTE_MASK;
        if (index < 3U) {
            g_Game.members[index].u.turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
            return;
        }
        ENEMY_COMBATANT(index).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
    }
}
