#include "engine/slus/slus.h"

/* clears the record fields of the three 0x140-stride slots whose mode flag
 * is set.
 */
MATCH void Party_ClearActiveBattlers(void) {
    s32 index;

    index = 0;
    while ((index & 0xFF) < 3U) {
        if (g_BattlePartyBattlers[index & 0xFF].header.flags != 0) {
            Party_ClearBattlerState(index & 0xFF);
        }
        index++;
    }
}
