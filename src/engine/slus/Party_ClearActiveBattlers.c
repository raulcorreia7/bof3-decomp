#include "engine/slus/slus.h"

/* clears the record fields of the three 0x140-stride slots whose mode flag
 * is set.
 */
MATCH void Party_ClearActiveBattlers(void) {
    s32 index;

    index = 0;
    while ((u32)(index & BYTE_MASK) < 3U) {
        if (g_BattlePartyBattlers[index & BYTE_MASK].flags_00 != 0) {
            Party_ClearBattlerState(index & BYTE_MASK);
        }
        index++;
    }
}
