#include "engine/slus/slus.h"

/* publishes each of the four field work records as the scratchpad
 * work pointer and steps the ones that are active and not yet flagged 0x40.
 */
MATCH void Area_UpdateParty(void) {
    u8 index;

    for (index = 0; index < 4; index++) {
        u8* work;

        work   = (u8*)&g_PartyActors[index];
        g_Task = work;

        if (((work[0] & 0x1u) != 0u) && ((work[0] & 0x40u) == 0u)) {
            Actor_ProjectForDraw();
        }
    }
}
