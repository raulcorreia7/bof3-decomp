#include "engine/slus/slus.h"

/* starts the transfer of slot: loads its start sector and, from its TOC entry, size, load argument,
 * first word and type into the active loader state; returns 0 when the slot is past the entry count or a
 * stream flag skips a type below 6.
 */
MATCH s32 EMI_LoaderNextRead(u8 slot) {
    volatile EmiTocEntry* slot_table;
    s32                   result;
    u32                   first_sector;

    if (*D_80146848 < slot) {
        return 0;
    }
    if (((g_EmiStreamFlags & 0x20u) != 0) && (D_80146844.slots[slot].type < 6u)) {
        return 0;
    }

    if (slot == 0u) {
        first_sector   = g_EmiSlotSectors[0];
        g_EmiBytesLeft = 0x800;
        /* FAKE: statement boundary keeps the retail register order and schedule; the plain form without barriers is 12 bytes short. */
        ORDER_LOCK(g_EmiEntryType = EMI_LOADER_STATE_ARCHIVE_HEADER);
        /* FAKE: barrier holds the return constant after the loader stores.
         */
        MATCH_BARRIER();
        result             = 1;
        g_EmiStep          = result;
        g_EmiPayloadSector = first_sector;
    } else {
        g_EmiPayloadSector = g_EmiSlotSectors[slot];
        slot_table         = D_80146844.slots - -slot;
        g_EmiBytesLeft     = slot_table->size;
        g_EmiLoadArg       = slot_table->load_arg;
        g_EmiFirstWord     = slot_table->first_word;
        g_EmiStep          = 0;
        g_EmiEntryType     = slot_table->type;
        /* FAKE: barrier holds the return constant after the state store. */
        MATCH_BARRIER();
        result = 1;
    }

    return result;
}
