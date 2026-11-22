#include "engine/slus/slus.h"

/* clears the mode flag and record fields of the three 0x140-stride slots.
 */
MATCH void Party_BattlersReset(void) {
    s32 index;

    index = 0;
    while ((index & BYTE_MASK) < 3U) {
        g_Game.members[index & BYTE_MASK].header.flags = 0;
        Party_BattlersClearState(index & BYTE_MASK);
        index++;
    }
}
