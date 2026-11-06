#include "engine/slus/slus.h"

/* clears the mode flag and record fields of the three 0x140-stride slots.
 */
MATCH void Party_ResetBattlers(void) {
    s32 index;

    index = 0;
    while ((index & 0xFF) < 3U) {
        g_BattlePartyBattlers[index & 0xFF].header.flags = 0;
        Party_ClearBattlerState(index & 0xFF);
        index++;
    }
}
