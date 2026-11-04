#include "area103_13.h"

/* func_801F56B0 */
MATCH u8 Area_FindTaggedPartySlot(void) {
    u8 slot;
    u8 member;

    for (slot = 0; slot < 3; slot++) {
        for (member = 0; member < g_PartySize; member++) {
            if (D_801F5D64[slot] == D_80145F09[member][0]) {
                return slot;
            }
        }
    }
    return 0xFF;
}
