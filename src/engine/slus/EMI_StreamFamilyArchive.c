#include "engine/slus/slus.h"

/*
 * maps a BOF3 content family plus index into the slot id used by the
 * EXE loader path.
 */
MATCH void EMI_StreamFamilyArchive(u8 index, u8 family) {
    /* FAKE: retail holds the switch index in a0. */
    MATCH_REG(u8, archive_index, "a0");
    u8* hint;
    u32 emi_id;

    archive_index = index;
    if (family != 3u) {
        hint = &g_EmiLoadedCharacterIndex;
        if (family == 0u) {
            *hint = index | EMI_LOADED_PL;
        } else {
            *hint = archive_index;
        }
    }

    switch (family) {
        case EMI_FAMILY_PL:
            emi_id = archive_index + EMI_SLOT_PL;
            break;
        case EMI_FAMILY_BPLD:
            emi_id = archive_index + EMI_SLOT_BPLD;
            break;
        case EMI_FAMILY_BPLU:
            emi_id = archive_index + EMI_SLOT_BPLU;
            break;
        case EMI_FAMILY_PLP:
            emi_id = archive_index + EMI_SLOT_PLP;
            break;
        default:
            return;
    }

    EMI_LoaderStreamInitSlot(emi_id);
}
