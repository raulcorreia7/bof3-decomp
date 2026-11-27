#include "engine/slus/slus.h"

/* publishes each of the four field work records as the scratchpad
 * work pointer and steps the ones that are active and not yet flagged 0x40.
 */
MATCH void Area_UpdateParty(void) {
    u8 index;

    for (index = 0; index < 4; index++) {
        Actor* work;

        work = &g_PartyActors[index];
        SELF_SET(work);

        if ((work->header.flags & ACTOR_FLAG_IN_USE) && ((work->header.flags & 0x40u) == 0u)) {
            Actor_ProjectForDraw();
        }
    }
}
