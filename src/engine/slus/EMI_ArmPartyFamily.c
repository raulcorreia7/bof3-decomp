#include "engine/slus/slus.h"

/* resolves the three-byte family key through EMI_FindPartyArchive and re-arms the loader through
 * EMI_FamilySlot unless the index already matches g_EmiLoadedCharacterIndex. The family-0 spelling is the one
 * func_8016728C stages (index | 0x80); other families compare the plain index, and a match takes the shared exit
 * untouched.
 */
MATCH void EMI_ArmPartyFamily(u8 member_a, u8 member_b, u8 member_c, u8 family) {
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
    EMI_StreamFamilyArchive(slot, family);
}
