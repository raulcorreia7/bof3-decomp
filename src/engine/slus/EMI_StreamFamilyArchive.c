#include "engine/slus/slus.h"

/*
 * maps a BOF3 content family plus index into the slot id used by the
 * EXE loader path.
 */
MATCH void EMI_StreamFamilyArchive(u8 index, u8 family) {
    /* FAKE: retail holds the switch index in a0. */
    MATCH_REG(u8, slot_index, "a0");
    u8* hint;
    u32 slot_id;

    slot_index = index;
    if (family != 3u) {
        hint = &g_EmiLoadedCharacterIndex;
        if (family == 0u) {
            *hint = index | EMI_LOADED_PL;
        } else {
            *hint = slot_index;
        }
    }

    switch (family) {
        case EMI_FAMILY_PL:
            slot_id = slot_index + EMI_SLOT_PL;
            break;
        case EMI_FAMILY_BPLD:
            slot_id = slot_index + EMI_SLOT_BPLD;
            break;
        case EMI_FAMILY_BPLU:
            slot_id = slot_index + EMI_SLOT_BPLU;
            break;
        case EMI_FAMILY_PLP:
            slot_id = slot_index + EMI_SLOT_PLP;
            break;
        default:
            return;
    }

    EMI_LoaderStreamInitSlot(slot_id);
}
