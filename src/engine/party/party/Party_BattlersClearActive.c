#include "engine/slus/slus.h"

/* clears the record fields of the three 0x140-stride slots whose mode flag
 * is set.
 */
MATCH void Party_BattlersClearActive(void) {
    s32 index;

    index = 0;
    while ((index & BYTE_MASK) < 3U) {
        if (g_Game.members[index & BYTE_MASK].header.flags != 0) {
            Party_BattlersClearState(index & BYTE_MASK);
        }
        index++;
    }
}
