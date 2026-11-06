#include "battle_15.h"

/* marks battlers as damaged: bit 0x80 of the selector loops over
 * the three player rows, bit 0x40 over the eleven enemy rows, and a selector
 * without bits 0xC0 marks only the one indexed battler.
 */
MATCH void func_800A9820(u8 selector) {
    s32 i;
    u8  index;

    if (selector & 0xC0) {
        if (selector & 0x80) {
            for (i = 0; (u32)(i & 0xFF) < BATTLE_PARTY_SLOT_COUNT; i++) {
                index = i & 0xFF;
                if ((Battle_SlotIsBlocked(index) & 0xFF) == 0) {
                    g_BattlePartyBattlers[index].turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
                }
            }
        }
        if (selector & 0x40) {
            for (i = 3; (u32)(i & 0xFF) < COMBATANT_COUNT; i++) {
                index = i & 0xFF;
                if ((Battle_SlotIsBlocked(index) & 0xFF) == 0) {
                    ENEMY_COMBATANT(index).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
                }
            }
        }
    } else {
        index = selector & 0xFF;
        if (index < 3U) {
            g_BattlePartyBattlers[index].turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
            return;
        }
        ENEMY_COMBATANT(index).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGED;
    }
}
