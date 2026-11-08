#include "battle_15.h"

/* maps an agility difference to an escape threshold: table value for
 * the 16-wide bucket of diff + 0x20, +8 when the flag byte is 2, +8 when a live
 * slot has bit 0x2000 set, capped at 0x40.
 */
MATCH u8 func_8009BACC(s32 diff) {
    u8 result;
    u8 slot;

    result = 0;
    diff += 0x20;
    diff = diff / 16;
    if (diff < 0) {
        result = 0x1C;
    }
    if (diff >= 6) {
        result = 0x38;
    }
    if (result == 0) {
        result = g_BattleEscapeThresholds[diff];
    }
    if (g_Battle.outcome.attempts == 2) {
        result += 8;
    }
    for (slot = 0; slot < g_Battle.party_count; slot++) {
        if (!Battle_SlotIsBlocked(slot) && HAS_STATUS(g_Game.members[slot], 0x2000)) {
            result += 8;
            break;
        }
    }
    result = MIN(result, 0x40);
    return result;
}
