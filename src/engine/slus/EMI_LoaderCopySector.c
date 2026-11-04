#include "engine/slus/slus.h"

/* copies the next EMI transfer chunk from the CD sector buffer,
 * wrapping into the active slot's sector when a partial sector remains.
 */
MATCH void EMI_LoaderCopySector(void) {
    u32  transfer_words;
    u32  transfer_size;
    u32  transfer_address;
    u32* transfer_size_ptr;

    transfer_size_ptr = (u32*)&g_EmiBytesLeft;
    transfer_size     = *transfer_size_ptr;
    if (transfer_size >= 0x801u) {
        *transfer_size_ptr = transfer_size - 0x800u;
        CdGetSector((void*)g_EmiLoadArg, 0x200);
        g_EmiLoadArg += 0x800u;
    } else {
        transfer_address = g_EmiLoadArg;
        transfer_words   = (transfer_size + 3u) >> 2;
        CdGetSector((void*)transfer_address, transfer_words);

        if (transfer_words != 0x200u) {
            CdGetSector((void*)(g_EmiRingBase + ((s32)g_EmiRingSlot << 11)), 0x200u - transfer_words);
        }

        *transfer_size_ptr = 0;
        g_EmiLoadArg += transfer_words << 2;
    }
}
