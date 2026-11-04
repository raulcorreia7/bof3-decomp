#include "engine/slus/slus.h"

/* publishes each of the four field work records as the scratchpad
 * work pointer and steps the ones that are active and not yet flagged 0x40.
 */
MATCH void Area_RunParty(void) {
    u8 index;

    for (index = 0; index < 4; index++) {
        u8* work;

        work       = (u8*)&D_80147A58[index * ACTOR_SIZE];
        g_SpadWork = work;

        if (((work[0] & 1u) != 0u) && ((work[0] & 0x40u) == 0u)) {
            func_8015A944();
        }
    }
}
