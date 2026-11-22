#include "engine/slus/slus.h"

/* Loads the PLPxxx character program for the three members when its archive index differs from the one in
 * the low seven bits of g_EmiLoadedCharacterIndex.
 */
MATCH void EMI_PartyLoadCode(u8 member_a, u8 member_b, u8 member_c) {
    u8 slot;

    slot = EMI_PartyFindArchive(member_a, member_b, member_c);
    if ((g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) != slot) {
        EMI_ArchiveLoadFamily(slot, EMI_FAMILY_PLP);
    }
}
