#include "engine/slus/slus.h"

/* resolves the three-byte family key through EMI_FindPartyArchive and, when
 * the resolved index differs from the current selection id in the low seven
 * bits of g_EmiLoadedCharacterIndex, re-arms the loader with that index's family-3
 * slot through EMI_FamilySlot.
 */
MATCH void EMI_ArmPartyPlp(u8 member_a, u8 member_b, u8 member_c) {
    u8 slot;

    slot = EMI_FindPartyArchive(member_a, member_b, member_c);
    if ((g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) != slot) {
        EMI_StreamFamilyArchive(slot, EMI_FAMILY_PLP);
    }
}
