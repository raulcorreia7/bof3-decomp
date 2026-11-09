#include "engine/slus/slus.h"

/* Loads the party's character data for the three members. */
MATCH void EMI_LoadPartyData(u8 member_a, u8 member_b, u8 member_c, u8 family) {
    u8  slot;
    s32 hint;

    slot = EMI_FindPartyArchive(member_a, member_b, member_c);
    hint = g_EmiLoadedCharacterIndex;
    if (family != 0u) {
        if (hint != slot) {
            goto rearm; /* retail shares one re-arm call between both families */
        }
        return;
    }
    if (hint == (slot | 0x80u)) {
        return;
    }
rearm:
    EMI_GetArchiveId(slot, family);
}
